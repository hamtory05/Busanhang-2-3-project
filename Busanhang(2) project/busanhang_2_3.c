#include <stdio.h> 
#include <stdlib.h> 

// --<< 변수 정리 >>--  

// [ PDF 2-2. 부산헹(1)에서 수정 ]
// 1) 파라미터 
#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5 
#define PROB_MIN 10 // 확률 
#define PROB_MAX 90 
#define AGGRO_MIN 0 // 어그로 범위 
#define AGGRO_MAX 5

// [ PDF 2-2. 부산헹(1)에서 수정 ]
// 2) 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// [ PDF 2-2. 부산헹(1)에서 수정 ]
// 3) 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// [ PDF 2-2. 부산헹(1)에서 수정 ]
// 4) 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// [ PDF 2-1 ~ 3-4에 쓰이는 변수들 ]
// 5) 전역 변수
int train_length; // 기차 길이
int madongseok_stamina; //마동석 체력 
int pre_madongseok_stamina; // 마동석 (전) 체력 상태
int probability; // 확률
int p; // 확률 (줄임말)
int citizen; // 시민 1
int pre_citizen; // 시민 1 (전) 상태 
int zombie; // 좀비
int pre_zombie; // 좀비 (전) 상태
int madongseok; // 마동석
int pre_madongseok; // 마동석 (전) 상태
int citizen_aggro = 1; // 시민 1 어그로
int pre_citizen_aggro; // 시민 1 (전) 어그로
int madongseok_aggro = 1; // 마동석 어그로
int pre_madongseok_aggro; // 마동석 (전) 어그로
int madongseok_move; // 마동석 이동
int phase = 1; // 턴
int madongseok_action; // 마동석 행동
int zombie_move_or_not = 1; // 좀비가 마동석의 붙잡기에 따라 움직일지 안 움직일지 정하기
int r, k; // 시민, 마동석 난수 
int villain; // 빌런
int pre_villain; // 빌런 (전) 상태
int j; // 빌런 난수 
int villain_aggro; // 빌런 어그로
int villain_pre_aggro; // 빌런 (전) 어그로 상태
int villain_dead = 0; // 빌런이 죽었을 때 +1 카운트 되는 변수
int citizen_dead = 0;  // 시민이 죽었을 때 +1 카운트 되는 변수
int madongseok_dead = 0; // 마동석이 죽었을 때 +1 카운트 되는 변수 
int stage = 1;

// --<< 필요한 함수 정의 >>--

// 모든 변수 초기화 함수
void reset_func(); // 부산헹 한 파트가 끝나면 모든 변수를 초기화 한 후 다시 처음부터 시작하게 하기 위한 함수
void reset_func() {
	int citizen_aggro = 1; // 시민 1 어그로
	int madongseok_aggro = 1; // 마동석 어그로
	int zombie_move_or_not = 1; // 좀비가 마동석의 붙잡기에 따라 움직일지 안 움직일지 정하기
	int villain_dead = 0; // 빌런이 죽었을 때 +1 카운트 되는 변수
	int citizen_dead = 0;  // 시민이 죽었을 때 +1 카운트 되는 변수
	int madongseok_dead = 0; // 마동석이 죽었을 때 +1 카운트 되는 변수 
	int citizens_number_select_list[LEN_MAX] = { 0 }; // 시민 생성 및 위치 배열
	int citizens_aggro_list[LEN_MAX] = { 0 }; // 시민 어그로 배열
	int citizens_move_list[LEN_MAX] = { 0 }; // 시민이 움직였는지 여부를 판단하는 배열
	int citizens_safe_list[LEN_MAX] = { 0 }; // 시민이 탈출했을 때 +1 되는 배열
	int citizens_safe_or_dead_list[LEN_MAX] = { 0 }; // 시민이 탈출했거나 죽었을 때 +1 올려서 더이상 시민들 움직임이 출력되지않게 하는 변수
	int citizens_can_move = 0; // 시민들 이동 가능 여부
	int citizens_check = 0;
	int zombie_move_check = 0;
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 1) 기차 길이 (입력 및 예외처리) 함수 선언 및 입력 메시지	
void train_length_func(); // 기차 길이 (입력 및 예외처리) 함수
void train_length_message_func(); // 기차 길이 입력 메시지

// 1-1 기차 길이 입력 메시지 함수
void train_length_message_func() {
	printf("train length(%d ~ %d)>>", LEN_MIN, LEN_MAX);
}
// 1-2) 기차 길이 (입력 및 예외처리) 함수
void train_length_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		train_length_message_func();
		scanf_s("%d", &train_length);
		// 기차 길이가 15 ~ 50 사이일 때
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			break;
		}
	}
	// * 마동석, 시민 1, 좀비 초기 위치 설정 *
	madongseok = train_length - 2;
	zombie = train_length - 3;
	citizen = train_length - 6;
	pre_citizen = citizen;
	pre_zombie = zombie;
	pre_madongseok = madongseok;
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 2) 마동석 체력 (입력 및 예외처리) 함수 선언 및 입력 메시지
void madongseok_stamina_func(); // 마동석 체력 (입력 및 예외처리) 함수
void madongseok_stamina_message_func(); //  마동석 체력 입력 메시지

// 2-1) 마동석 체력 입력 메시지
void madongseok_stamina_message_func() {
	printf("madongseok stamina(%d ~ %d)>>", STM_MIN, STM_MAX);
}

// 2-2) 마동석 체력 (입력 및 예외처리) 함수
void madongseok_stamina_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		madongseok_stamina_message_func();
		scanf_s("%d", &madongseok_stamina);
		// 마동석 체력이 0~5 사이일 때
		if (madongseok_stamina >= STM_MIN && madongseok_stamina <= STM_MAX) {
			break;
		}
	}
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 3) 확률 (입력 및 예외처리) 함수 선언 및 입력 메시지
void probability_func();
void probability_message_func();

// 3-1) 확률 입력 메시지 
void probability_message_func() {
	printf("percentile probability 'p'(%d ~ %d)>>", PROB_MIN, PROB_MAX);
}

// 3-2) 확률 (입력 및 예외처리) 함수
void probability_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		probability_message_func();
		scanf_s("%d", &probability);
		p = probability;
		// 확률이 10 ~ 90 사이일 때
		if (p >= PROB_MIN && p <= PROB_MAX) {
			return p;
			break;
		}
	}
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 4) 기차 상태 (첫째, 둘째, 셋째 줄) 함수 선언
void train_shape_first_third_func();
void train_shape_second_func();
void train_shape_main_func();

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 4-1) 기차 첫째 줄, 셋째 줄
void train_shape_first_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 4-2) 기차 둘째 줄
void train_shape_second_func() {
	for (int i = 0; i < train_length; i++) {
		// 기차의 처음과 끝을 '#' 으로 마무리
		if (i == 0 || i == train_length - 1) {
			printf("#");
		}
		else if (i == citizen) {
			printf("C");
		}
		else if (i == zombie) {
			printf("Z");
		}
		else if (i == madongseok) {
			printf("M");
		}
		else {
			printf(" ");
		}
	}
	printf("\n");
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 4-3) 기차 (1 ~ 3 줄) 모음 함수
void train_shape_main_func() {
	train_shape_first_third_func();
	train_shape_second_func();
	train_shape_first_third_func();
}

// [ PDF 2-3 < 이동 > &2 - 3 < 이동 > :예외처리 ]
// 5) 마동석 이동 (입력 및 예외처리) 함수 선언 및 입력 메세지
void madongseok_move_func();
void madongseok_move_select_message_func();
void madongseok_move_select_message_1_func();

// 5-1) 마동석 이동 입력 메세지
void madongseok_move_select_message_func() {
	printf("madongseok move(0:stay)>>");
}

// 5-2) 마동석 이동 입력 메시지 (2)
void madongseok_move_select_message_1_func() {
	printf("madongseok move(0:stay, 1:left)>>");
}

// 5-3) 마동석 이동 (입력 및 예외처리) 함수 선언
void madongseok_move_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		// 좀비가 마동석 옆에 있을 때
		if (zombie + 1 == madongseok) {
			madongseok_move_select_message_func();
			scanf_s("%d", &madongseok_move);
			// 마동석 이동이 0일 때 무한반복 나오기
			if (madongseok_move == 0) {
				break;
			}
		}
		else {
			// 좀비가 마동석 옆에 없을 때
			madongseok_move_select_message_1_func(); 
			scanf_s("%d", &madongseok_move);
			// 마동석 이동이 0 또는 1일 때 무한반복 나오기
			if (madongseok_move == 1) {
				madongseok -= 1;
				break;
			}
			else {
				break;
			}
		}
	}
}

// [ PDF 2-2 ~ 2-4에 쓰이는 함수들 모음 ]
// 6) 시민(어그로 포함) 좀비 이동 함수 선언 
void citizen_move_func(); // 시민 이동 함수
void citizen_aggro_max_func(); // 시민 최대 어그로 (예외처리) 함수
void citizen_move_left_func(); // 시민 이동 (왼쪽 한칸) 함수
void citizen_move_stay_func(); // 시민 이동 (왼쪽 한칸 X) 함수
void citizen_move_or_nomove_func(); // 시민이 citizen_move_func() 으로 움직였을 때 또는 안 움직였을 때
void zombie_move_func(); // 좀비 이동 함수
void zombie_cannot_move_func(); // 좀비 이동(X) 함수
void zombie_move_or_not_func(); //  마동석이 좀비 붙들기에 성공했을때 or 실패했을 때의 좀비 이동 상태 함수
void zombie_move_or_nomove_func(); // 좀비가 zombie_move_func() 으로 움직였을 때 또는 안 움직였을 때
void zombie_move_citizen_func(); // 좀비 -> 시민 이동 함수
void zombie_move_madongseok_func(); // 좀비 -> 마동석 이동 함수
void madongseok_aggro_biggerthan_citizen_func(); // 마동석 어그로가 시민 어그로보다 클 때
void zombie_attack_madongseok_message_func(); // 좀비가 마동석을 공격했을 때 출력되는 메세지
void citizen_stay_message_func(); // 시민이 움직이지 않았을 때 출력되는 메세지
void citizen_move_message_func(); // 시민이 움직였을 때 출력되는 메세지
void zombie_stay_message_func(); // 좀비가 움직이지 않았을 때 출력되는 메세지
void zombie_move_message_func(); // 좀비가 움직였을 때 출력되는 메세지
void zombie_cannot_move_message_func(); // 좀비가 움직일 수 없는 턴일 때 출력되는 메세지

// [ PDF 2-3 <이동> & 2-3 <이동>: 예외처리 ]
// 6-0) 입력 메세지 모음
void zombie_attack_madongseok_message_func() {
	printf("zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina : %d -> %d)\n", citizen_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

void citizen_stay_message_func() {
	printf("citizen: stay %d (aggro: %d -> %d)\n", citizen, pre_citizen_aggro, citizen_aggro);
}

void citizen_move_message_func() {
	printf("citizen: %d -> %d (aggro: %d -> %d)\n", pre_citizen, citizen, pre_citizen_aggro, citizen_aggro);
}

void zombie_stay_message_func() {
	printf("zombie: stay %d\n", zombie);
}

void zombie_move_message_func() {
	printf("zombie: %d -> %d\n", pre_zombie, zombie);
}

void zombie_cannot_move_message_func() {
	printf("zombie cannot move this turn\n");
}

// [ PDF 2-3 <이동> & 2-3 <이동>: 예외처리 ]
// 6-1) 시민 이동 (왼쪽 한칸) 함수
void citizen_move_left_func() {
	pre_citizen = citizen;
	citizen -= 1;
	pre_citizen_aggro = citizen_aggro;
	// 시민 어그로가 최대가 되면 최대 어그로로 고정.
	if (citizen_aggro >= AGGRO_MAX) {
		citizen_aggro = AGGRO_MAX;
	}
	else {
		citizen_aggro += 1;
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-2) 시민 최대 어그로 (예외처리) 함수
void citizen_aggro_max_func() {
	pre_citizen_aggro = citizen_aggro;
	if (citizen_aggro <= AGGRO_MIN) {
		citizen_aggro = AGGRO_MIN;
	}
	else {
		citizen_aggro -= 1;
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-3) 시민 이동 (왼쪽 한칸 X) 함수
void citizen_move_stay_func() {
	citizen_aggro_max_func();
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-4) 시민 이동 메인 함수 
void citizen_move_func() {
	if (100 - p >= r) {
		citizen_move_left_func();
	}
	else {
		citizen_move_stay_func();
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-5) 마동석 어그로가 시민 어그로보다 클 때의 함수
void madongseok_aggro_biggerthan_citizen_func() {
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_stamina -= 1;
	zombie_attack_madongseok_message_func();
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-6) 시민이 citizen_move_func() 으로 인해 움직였을 때 또는 안 움직였을 때
void citizen_move_or_nomove_func() {
	if (citizen_dead == 0) {
		if (citizen == pre_citizen) { // 시민이 움직이지 않았을 때
			if (citizen_aggro == AGGRO_MIN) { // 시민 어그로가 0일 때
				citizen_stay_message_func();
			}
			else { // 시민 어그로가 0이 아닐 때
				citizen_stay_message_func();
			}
		}
		else { // 시민이 움직였을 때
			citizen_move_message_func();
		}
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-7) 좀비 이동 함수
void zombie_move_func() {
	if (phase % 2 == 1) { // 턴이 홀수일 때 (즉, 2턴마다)
		if (zombie_move_or_not == 1) { // 마동석이 붙들기에 실패했을 때
			if (citizen_aggro > madongseok_aggro) { // 시민 어그로가 마동석 어그로보다 클 때
				zombie_move_citizen_func();

			}
			else if (madongseok_aggro > citizen_aggro) { // 마동석 어그로가 시민 어그로보다 클 때
				zombie_move_madongseok_func();

			}
			else { // 시민 어그로와 마동석 어그로가 같을 때
				zombie_move_citizen_func();

			}
		}
	}
	else { // 짝수턴일 때
		
	}
}

// [ PDF 2-4 <행동> & 2-4 <행동> : 예외처리 ]
// 6-8) 좀비 이동(X) 함수 -> 만들 필요는 없지만 시민 이동 출력하는거랑 같이 출력하게 하기 위해서 어쩔수없이 따로 만들었음.
void zombie_cannot_move_func() {
	if (phase % 2 == 0) {
		zombie_cannot_move_message_func();
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-9) zombie_move_func()으로 좀비가 움직였을 때 또는 안 움직였을 때
void zombie_move_or_nomove_func() {
	if (phase % 2 == 1) { // 홀수턴일때
		if (zombie_move_or_not == 1) { // 마동석이 붙들기 함수에서 실패했을 때
			if (zombie == pre_zombie) { // 좀비가 그 자리에 있을 때
				zombie_stay_message_func();
			}
			else { // 좀비가 움직였을때
				zombie_move_message_func();
			}
		}
		else { // 마동석이 붙들기 함수에서 성공했을 때
			zombie_cannot_move_message_func();
		}
	}
}

// [ PDF 2-4 <행동> & 2-4 <행동> : 예외처리 ]
// 6-10) 마동석이 좀비 붙들기에 성공했을때 or 실패했을 때의 좀비 이동 상태 함수
void zombie_move_or_not_func() {
	if (zombie_move_or_not == 0) { // 좀비 붙들기에 성공했을 때
		phase = 1; // 턴을 강제로 홀수로 변경 -> 홀수로 바뀌고 메인 코드 마지막 +1 되면서 담턴에 좀비가 못 움직이게 됨.
	}
	else { // 좀비 붙들기에 실패했을 때
		phase = phase;
	}
}


// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ], [ PDF 2-4 <행동> & 2-4 <행동> : 예외처리 ]
// 6-11) 좀비 -> 마동석 이동 함수
void zombie_move_madongseok_func() {
	// 마동석이 좀비 붙들기를 성공했을 때 (좀비 이동 불가)
	zombie_move_or_not_func();
	// 마동석과 이미 민접해 있을 때
	if (zombie + 1 == madongseok) {
		zombie = zombie;
	}
	else { // 민접해 있지 않을 때
		pre_zombie = zombie;
		zombie += 1;
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ], [ PDF 2-4 <행동> & 2-4 <행동> : 예외처리 ]
// 6-12) 좀비 -> 시민 이동 함수
void zombie_move_citizen_func() {
	// 마동석이 좀비 붙들기를 성공했을 때 (좀비 이동 불가)
	zombie_move_or_not_func();
	// 시민과 이미 민접해 있을 때
	if (zombie - 1 == citizen) {
		zombie = zombie;
	}
	else { // 민접해 있지 않을 때
		pre_zombie = zombie;
		zombie -= 1;
	}
}

// [ PDF 2-2 ~ 2-4에 쓰이는 함수들 모음 ]
// 7) 마동석 행동 함수 선언 
void madongseok_action_func(); // 마동석 행동 메인 함수
void madongseok_action_0_func(); // 마동석 행동이 0을 입력 받았을 때의 함수
void madongseok_action_1_func(); // 마동석 행동이 1을 입력 받았을 때의 함수
void madongseok_action_2_func(); // 마동석 행동이 2를 입력 받았을 때의 함수
void madongseok_action_withzombie_func(); // 마동석이 좀비와 인접한 경우의 함수
void madongseok_aggro_max_func(); // 마동석 어그로가 최대를 넘지 않기 위한 함수
void madongseok_action_start_func(); // 마동석 행동 입력 받았을 때 실행시킬 함수
void madongseok_move_0_func(); // 마동석 이동이 0을 입력 받았을 때의 함수
void madongseok_move_1_func(); // 마동석 이동이 1을 입력 받았을 때의 함수
void madongseok_action_yesorno_func(); // 마동석 행동 여부 함수
void madongseok_move_main_func(); // 마동석 이동 메인 함수
void madongseok_rest_message_func(); // 마동석 휴식 메세지
void madongseok_stay_action_message_func(); // 마동석 움직이지 않을 때 메세지 (행동)
void madongseok_move_message_func();  // 마동석 움직였을 때 메세지
void madongseok_provoke_message_func(); // 마동석 도발 메세지
void madongseok_pull_zombie_message_func(); // 마동석이 좀비 묶기에 성공했을 때의 메세지
void madongseok_fail_pull_zombie_message_func(); // 마동석이 좀비 묶기에 실패했을 때 메세지
void madongseok_action_select_message_func(); // 마동석 행동 선택 메세지 (좀비와 인접할 때)
void madongseok_action_1_select_message_func(); // 마동석 행동 선택 메세지 (좀비와 인접 X)
void madongseok_stay_move_message_func(); // 마동석 움직이지 않았을 때 메세지 (이동)

// 7-0) 마동석 행동 및 이동에 쓰이는 메세지 모음
void madongseok_rest_message_func() {
	printf("madongseok rests...\n");
}

void madongseok_stay_action_message_func() {
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

void madongseok_stay_move_message_func() {
	printf("madongseok: stay %d (aggro: %d -> %d, stamina: %d)", madongseok, pre_madongseok_aggro, madongseok_aggro, madongseok_stamina);
}

void madongseok_move_message_func() {
	printf("madongseok: %d -> %d (aggro: %d -> %d, stamina: %d)\n", pre_madongseok, madongseok, pre_madongseok_aggro, madongseok_aggro, madongseok_stamina);
}

void madongseok_provoke_message_func() {
	printf("madongseok provoked zomebie...\n");
	printf("madongseok : %d (aggro: %d -> %d, stamina: %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, madongseok_stamina);
}

void madongseok_pull_zombie_message_func() {
	printf("madongseok pulled zombie... Next turn, it can't move\n");
}

void madongseok_fail_pull_zombie_message_func() {
	printf("madongseok failed to pull zombie\n");
}

void madongseok_action_select_message_func() {
	printf("madongseok action(0. rest, 1.provoke, 2.pull)>>");
}

void madongseok_action_1_select_message_func() {
	printf("madongseok action(0.rest, 1.provoke)>>");
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-1) 마동석 (action) 휴식 함수 (0을 입력 받았을 때)
void madongseok_action_0_func() {
	madongseok_rest_message_func();
	pre_madongseok_aggro = madongseok_aggro;
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_aggro -= 1;
	madongseok_stamina += 1;
	if (madongseok_aggro <= AGGRO_MIN) { // 마동석 어그로가 ARRGO_MIN보다 작아질 때
		madongseok_aggro = AGGRO_MIN;
	}
	else {

	}
	if (madongseok_stamina >= STM_MAX) { // 마동석 체력이 STM_MAX 보다 커질 때
		madongseok_stamina = STM_MAX;
	}
	else {

	}
	madongseok_stay_action_message_func();  
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-2) 마동석 (move) 휴식 함수 (0을 입력받았을 때)
void madongseok_move_0_func() {
	madongseok_aggro -= 1;
	if (madongseok_aggro <= AGGRO_MIN) {
		madongseok_aggro = AGGRO_MIN;
	}
	else {

	}
	madongseok_stay_move_message_func();
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-3) 마동석 (move) 왼쪽으로 이동 했을 때 함수 (1을 입력했을 때) 
void madongseok_move_1_func() {
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro += 1;
	if (madongseok_aggro >= AGGRO_MAX) {
		madongseok_aggro = AGGRO_MAX;
	}
	else {

	}
	madongseok_move_message_func();
}
// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-4) 마동석 이동 정리 함수
void madongseok_move_main_func() {
	if (madongseok_move == 0) { // 0을 입력받았을 때
		madongseok_move_0_func();
	}
	else { // 1를 입력 받았을 때
		madongseok_move_1_func();
	}
}



// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-5) 마동석 최대 어그로 및 스테미나 (2번 입력 행동부분 예외처리) 함수 선언
void madongseok_aggro_max_func() {
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro += 2;
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_stamina -= 1;
	// 마동석 체력이 0 아래로 내려갔을 때
	if (madongseok_stamina < STM_MIN) {
		madongseok_stamina = STM_MIN;
	}
	// 마동석 어그로가 최대 어그로가 되었을 때
	if (madongseok_aggro >= AGGRO_MAX) {
		madongseok_aggro = 5;
	}
	else {
		madongseok_aggro += 1;
	}
	madongseok_stay_move_message_func();
}

// [ PDF 2-4 <행동> & <행동> : 예외처리
// 7-6) 마동석 도발 함수 (1을 입력 받았을 때) ]
void madongseok_action_1_func() {
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro = AGGRO_MAX;
	madongseok_provoke_message_func();
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-7) 마동석 붙들기 함수 (2를 입력 받았을 때)
void madongseok_action_2_func() {
	if (100 - p >= k) {
		zombie_move_or_not = 0; // 마동석이 좀비 붙들기에 성공했을 때 좀비가 못 움직이게 하기 위한 변수 
		madongseok_pull_zombie_message_func();
		madongseok_aggro_max_func();
		zombie_move_or_not_func();
	}
	else {
		zombie_move_or_not = 1; // 마동석이 좀비 붙들기에 실패했을 때 좀비가 움직이게 하기 위한 변수
		madongseok_fail_pull_zombie_message_func();
		madongseok_aggro_max_func();
		zombie_move_or_not_func();
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-8) 마동석 행동 입력 받았을 때 실행시킬 함수
void madongseok_action_start_func() {
	if (madongseok_action == 0) { // 0을 입력 받았을 때
		madongseok_action_0_func();  // 마동석 휴식 함수 불러오기
	}
	else if (madongseok_action == 1) { // 1을 입력 받았을 때
		madongseok_action_1_func(); // 마동석 도발 함수 불러오기
	}
	else if (madongseok_action == 2) { // 2를 입력 받았을 때
		madongseok_action_2_func(); //마동석 붙들기 함수 불러오기
	}
	else {

	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-9) 마동석 (좀비와 인접한 경우) 행동 규칙 함수
void madongseok_action_withzombie_func() {
	while (1) {
		madongseok_action_select_message_func();
		scanf_s("%d", &madongseok_action);
		printf("\n");
		if (madongseok_action > 2 && madongseok_action < 0) {
			continue;
		}
		else {
			madongseok_action_start_func();
			break;
		}
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-10) 마동석 행동 메인 함수 
void madongseok_action_func() {
	// 유효한 값이 입력될 때까지 무한 반복
	while (1) {
		madongseok_action_1_select_message_func();
		scanf_s("%d", &madongseok_action);
		printf("\n");
		if (zombie + 1 != madongseok) {
			if (madongseok_action == MOVE_STAY || madongseok_action == MOVE_LEFT) { // 0 또는 1을 입력했을 때
				if (madongseok_action == MOVE_STAY) { // 0을 입력했을 때 
					madongseok_action_0_func(); // 마동석 휴식 함수 불러오기
					break;
				}
				else { // 1을 입력했을 때
					madongseok_action_1_func(); // 마동석 도발 함수 불러오기
					break;
				}
			}
		}
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-11) 마동석 행동 여부 함수
void madongseok_action_yesorno_func() {
	if (madongseok == zombie + 1) { // 마동석이 좀비와 인접할 때
		madongseok_action_withzombie_func(); // 마동석 행동 함수 불러오기
	}
	else { // 마동석이 좀비와 인접하지 않을 때
		madongseok_action_func(); // 마동석 행동 함수 불러오기
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 8) 좀비 공격 여부에서 시민, 마동석이 죽었을 때의 함수
void citizen_aggro_biggerthan_madongseok_aggro_func(); // 시민 어그로가 마동석보다 클 때
void madongseok_aggro_biggerthan_citizen_aggro_func(); // 마동석의 어그로가 시민보다 클 때
void zombie_with_citizen_func(); // 좀비와 시민이 인접해있을 때
void madongseok_stamina_STM_MIN_func(); // 마동석 체력이 STM_MIN이 되었을 때
void citizen_madongseok_dead_func(); // 시민과 마동석이 죽었을 때의 함수
void citizen_dead_message_func(); // 시민이 죽었을 때 출력되는 메세지
void madongseok_dead_message_func(); // 마동석이 죽었을 때 출력되는 메세지
void zombie_attack_nobody_func(); // 좀비가 아무도 공격을 안 했을 때 출력되는 메세지

// 8-1) 시민이 죽었을 때 출력되는 메세지
void citizen_dead_message_func() {
	printf("GAME OVER! citizen dead...");
}

// 8-2) 마동석이 죽었을 때 출력되는 메세지
void madongseok_dead_message_func() {
	printf("GAME OVER! madongseok_dead...");
}

// 8-3) 좀비가 아무도 공격을 안 했을 때 출력되는 메세지
void zombie_attack_nobody_func() {
	printf("zombie attacked nobody.\n");
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 8-4) 시민의 어그로가 마동석보다 클 때
void citizen_aggro_biggerthan_madongseok_aggro_func() {
	if (citizen_aggro > madongseok_aggro) { // 시민의 어그로가 더 클 때
		citizen_dead_message_func();
		citizen_dead += 1;
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 8-5) 마동석의 어그로가 시민보다 클 때
void madongseok_aggro_biggerthan_citizen_aggro_func() {
	madongseok_aggro_biggerthan_citizen_func();
	if (madongseok_stamina == STM_MIN) { // 마동석 체력이 STM_MIN 일 때
		madongseok_dead_message_func(); 
		madongseok_dead += 1;
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 8-6) 좀비와 시민이 인접해있을 때
void zombie_with_citizen_func() {
	if (zombie - 1 == citizen) { // 좀비와 시민이 인접해있을 때
		citizen_dead_message_func();
		citizen_dead += 1;
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 8-7) 마동석 체력이 STM_MIN이 되었을 때
void madongseok_stamina_STM_MIN_func() {
	if (madongseok_stamina == STM_MIN) { // 마동석 체력이 STM_MIN 일 때
		madongseok_dead_message_func();
		madongseok_dead += 1;
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 8-8) 시민, 마동석이 죽었을 때의 메인 함수
void citizen_madongseok_dead_func() {
	if (zombie - 1 == citizen && zombie + 1 == madongseok) { // 좀비가 시민과 마동석 둘 다 인접해 있을 때
		citizen_aggro_biggerthan_madongseok_aggro_func(); // 시민의 어그로가 마동석보다 클 때
		madongseok_aggro_biggerthan_citizen_func(); // 마동석의 어그로가 시민보다 클 때
	}
	else if (zombie - 1 == citizen || zombie + 1 == madongseok) { // 좀비가 시민 또는 마동석 둘 중 한명에게 인접해있을 때
		zombie_with_citizen_func();
		madongseok_stamina_STM_MIN_func();
	}
	else {
		zombie_attack_nobody_func();
	}
}

// 9) --<<<  부산헹(2) 함수  >>>--
void busanhang2_func();

void busanhang2_func() {
	train_length_func(); // 기차 길이 출력(예외처리 O) 함수 불러오기
	madongseok_stamina_func(); // 마동석 체력 (예외처리 O) 함수 불러오기
	probability_func(); // 확률 입력 (예외처리 O) 함수 불러오기
	printf("\n");
	train_shape_main_func(); // 기차 초기 상태 불러오기
	printf("\n\n\n");
	// -< 메인 코드 메인 부분 >-
	while (1) {
		r = rand() % 101; // 시민 난수 출력
		k = rand() % 101; // 마동석 난수 출력
		citizen_move_func(); // 시민 이동 함수 불러오기
		zombie_move_func(); // 좀비 이동 함수 불러오기
		printf("\n");
		train_shape_main_func(); // 기차 상태 불러오기
		printf("\n");

		// citizen_move_func() 으로 인해 시민이 움직였을 경우 or 안 움직였을 경우
		citizen_move_or_nomove_func();

		// zombie_move_func() 으로 인해 좀비가 움직였을 경우 or 안 움직였을 경우
		zombie_move_or_nomove_func(); // 홀수턴일때
		zombie_cannot_move_func(); // 짝수턴일때

		printf("\n");
		madongseok_move_func(); // 마동석 이동 결정 함수
		printf("\n");
		train_shape_main_func(); // 기차 상태 출력 함수
		printf("\n\n");

		// 마동석 이동
		madongseok_move_main_func();

		printf("\n");

		printf("citizen does nothing.\n");

		// 시민이 탈출했을 때
		if (citizen == 1) {
			printf("GAME CLEAR! citizen safe !!");
			stage += 1;
			break;
		}

		// 좀비 공격으로 시민 또는 마동석이 죽었을 때
		citizen_madongseok_dead_func();
		if (citizen_dead == 1) {
			break;
		}
		else if (madongseok_dead == 1) {
			break;
		}

		// 마동석 행동 여부
		madongseok_action_yesorno_func(); 
		//
		phase += 1; // 턴을 1 증가시킨다.
	} // <- while 문 중괄호
	reset_func();
}

/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////


// --<< 부산헹(3) [ PDF 3-2 ] 추가된 전역 변수 >>--

// [ 부산헹(2) 함수들 안에 쓰여서 맨 위에다가 변수 선언을 하였음. ]
// int villain; // 빌런
// int pre_villain; // 빌런 (전) 상태
// int j; // 빌런 난수 
// int villain_aggro; // 빌런 어그로
// int villain_pre_aggro; // 빌런 (전) 어그로 상태
// int villain_dead = 0; // 빌런이 죽었을 때 주어지는 변수 값

// --<< 부산헹(3) [ PDF 3-2 ] 추가된 함수 정리 >>--

// 1) 기차 길이 (입력 및 예외처리) 함수 선언
void BSH3_2_train_length_func();
void BSH3_2_train_length_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		train_length_message_func();
		scanf_s("%d", &train_length);
		// 기차 길이가 15 ~ 50 사이일 때
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			break;
		}
	}
	// * 마동석, 시민 1, 빌런, 좀비 초기 위치 설정 *
	madongseok = train_length - 2;
	zombie = train_length - 3;
	citizen = train_length - 6;
	pre_citizen = citizen;
	villain = train_length - 5;
	pre_villain = villain;
	pre_zombie = zombie;
	pre_madongseok = madongseok;
}

// 2) 기차 모양 (시민, 빌런, 좀비, 마동석 위치) 함수 선언 
void BSH3_2_train_shape_main_func();
void BSH3_2_train_shape_first_third_func();
void BSH3_2_train_shape_second_func();

// 2-1) 기차 첫째 줄, 셋째 줄
void BSH3_2_train_shape_first_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// 2-2) 기차 둘째 줄
void BSH3_2_train_shape_second_func() {
	for (int i = 0; i < train_length; i++) {
		// 기차의 처음과 끝을 '#' 으로 마무리
		if (i == 0 || i == train_length - 1) {
			printf("#");
		}
		else if (i == citizen) {
			printf("C");
		}
		else if (i == villain && villain_dead == 0) {
			printf("V");
		}
		else if (i == zombie) {
			printf("Z");
		}
		else if (i == madongseok) {
			printf("M");
		}
		else {
			printf(" ");
		}
	}
	printf("\n");
}

// 2-3) 기차 함수 메인
void BSH3_2_train_shape_main_func() {
	BSH3_2_train_shape_first_third_func();
	BSH3_2_train_shape_second_func();
	BSH3_2_train_shape_first_third_func();
}

// 3) 빌런 이동 (발암 확률 & 어그로 예외처리) 함수 선언
void villain_move_func();
void villain_move_func() {
	if (citizen + 1 != villain) { // 빌런이 시민1과 인접해 있지 않을 때
		pre_villain = villain;
		villain = citizen + 1;
		villain_pre_aggro = villain_aggro;
		// 빌런 어그로가 AGGRO_MAX 일 때
		if (villain_aggro >= AGGRO_MAX) {
			villain_aggro = 5;
		}
		else { // 빌런 어그로가 AGGRO_MAX가 아닐 때
			villain_aggro += 1;
		}
	}
	else { // 빌런이 시민1과 인접해있을 때
		if (100 - p >= j) { // 빌런의 발암 시도가 성공했을 때
			pre_citizen = citizen; // 시민 1이 빌런 자리로 이동하기 전, 이동 전 변수에 저장
			citizen = villain; // 시민 1이 빌런 자리로 이동
			pre_villain = villain; // 빌런이 시민 1 자리로 이동하기 전, 이동 전 변수에 저장
			villain = pre_citizen; // 빌런이 시민 1 자리로 이동
		}
		else { // 빌런의 발암 시도가 실패했을 때
			// 아무 행동 없음
		}
	}
}

// 4) 빌런 어그로와 마동석 어그로가 같을 때의 함수 선언
void zombie_move_villain_func();
void zombie_move_villain_func() {
	if (zombie - 1 == villain) { // 좀비가 빌런이랑 인접할 때
		zombie = zombie;
	}
	else { // 인접해 있지 않을 때
		pre_zombie = zombie;
		zombie -= 1;
	}
}

// 5) 마동석 어그로가 빌런 어그로보다 더 클 때 함수 선언
void madongseok_aggro_biggerthan_villain_func();
void madongseok_aggro_biggerthan_villain_func() {
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_stamina -= 1;
	zombie_attack_madongseok_message_func();
}

// 6) villain_move_func() 으로 인해 빌런이 움직였을 경우 or 안 움직였을 경우 함수 선언 및 각종 메세지 함수
void villain_move_or_nomove_func();
void villain_stay_message_func(); // 빌런이 움직이지 않았을 때 출력되는 메세지
void villain_move_message_func(); // 빌런이 움직였을 때 출력되는 메세지

// 6-0) 빌런 메세지 함수 모음

void villain_stay_message_func() {
	printf("villain: stay %d (aggro: %d -> %d)\n", villain, villain_pre_aggro, villain_aggro);
}

void villain_move_message_func() {
	printf("villain: %d -> %d (aggro: %d -> %d)\n", pre_villain, villain, villain_pre_aggro, villain_aggro);
}

// 6-1) villain_move_func() 으로 인해 빌런이 움직였을 경우 or 안 움직였을 경우 함수
void villain_move_or_nomove_func() {
	if (villain_dead == 0) {
		if (villain == pre_villain) { // 빌런이 움직이지 않았을 때
			if (villain_aggro == AGGRO_MIN) { // 빌런 어그로가 0일 때
				villain_stay_message_func();
			}
			else { // 빌런 어그로가 0이 아닐 때
				villain_stay_message_func(); 
			}
		}
		else { // 빌런이 움직였을 때
			villain_move_message_func(); 
		}
	}
}

// 7) 좀비 공격으로 시민, 빌런, 마동석이 죽었을 대의 메인 함수 및 메세지
void madongseok_aggro_biggerthan_citizen_villain_aggro_func(); // 마동석 어그로가 시민, 빌런 어그로보다 클 때
void citizen_madongseok_villain_dead_func(); // 시민, 빌런, 마동석이 죽었을 때의 함수
void villain_aggro_biggerthan_madongseok_aggro_func(); // 빌런 어그로가 마동석 어그로보다 클 때
void villain_dead_message_func(); // 빌런이 죽었을 때 출력되는 메세지
void zombie_with_villain_func(); // 좀비와 빌런이 인접했을 때

// 7-0) 메세지 함수 모음
void villain_dead_message_func() {
	printf("villain dead...\n");
}


// 7-1) 마동석의 어그로가 시민. 빌런보다 클 때
void madongseok_aggro_biggerthan_citizen_villain_aggro_func() {
	if (madongseok_aggro > citizen || madongseok_aggro > villain_aggro) { // 마동석의 어그로가 더 클 때
		if (madongseok_aggro > citizen) {
			madongseok_aggro_biggerthan_citizen_func();
		}
		else {
			madongseok_aggro_biggerthan_villain_func();
		}
		if (madongseok_stamina == STM_MIN) { // 마동석 체력이 STM_MIN 일 때
			madongseok_dead_message_func();
			madongseok_dead += 1;
		}
	}
}

// 7-2) 빌런 어그로가 마동석 어그로보다 클 때
void villain_aggro_biggerthan_madongseok_aggro_func() {
	if (villain_dead == 0) {
		villain = -1;
		villain_dead += 1;
		villain_dead_message_func(); 
	}
}

//7-3) 좀비와 빌런이 인접했을 때
void zombie_with_villain_func() {
	if (villain == zombie - 1) { //  좀비와 빌런이 인접해있을 때
		if (villain_dead == 0) {
			villain = -1;
			villain_dead = 1;
			villain_dead_message_func();
		}
	}
}

// 좀비의 공격으로 시민, 빌런, 마동석이 죽었을 때의 메인 함수
void citizen_madongseok_villain_dead_func() {
	if (zombie - 1 == citizen && zombie + 1 == madongseok || zombie - 1 == villain && zombie + 1 == madongseok) { // 좀비가 시민과 마동석 둘 다 인접해 있을 때
		citizen_aggro_biggerthan_madongseok_aggro_func();
		madongseok_aggro_biggerthan_citizen_villain_aggro_func();
		villain_aggro_biggerthan_madongseok_aggro_func();
	}
	else if (zombie - 1 == citizen || zombie + 1 == madongseok || zombie - 1 == villain) { // 좀비가 시민 또는 마동석 또는 빌런 셋 중 한명에게 인접해있을 때
		zombie_with_citizen_func();
		madongseok_stamina_STM_MIN_func();
		zombie_with_villain_func();
	}
	else { // 셋 다 인접해있지 않을 때
		zombie_attack_nobody_func();
	}
}


// --<<<   부산헹(3) [ PDF 3-2. 스테이지2: 빌런 ]  >>>--
void busanhang3_2_func();
void busanhang3_2_func() {
	printf("3_2\n");
	BSH3_2_train_length_func(); // 기차 길이 출력(예외처리 O) 함수 불러오기
	madongseok_stamina_func(); // 마동석 체력 (예외처리 O) 함수 불러오기
	probability_func(); // 확률 입력 (예외처리 O) 함수 불러오기
	printf("\n");
	BSH3_2_train_shape_main_func(); // 기차 초기 상태 불러오기
	printf("\n\n\n");
	// -< 메인 코드 메인 부분 >-
	while (1) {
		r = rand() % 101; // 시민 난수 출력
		k = rand() % 101; // 마동석 난수 출력
		j = 30; // 빌런 발암 시도 확률
		citizen_move_func(); // 시민 이동 함수 불러오기
		villain_move_func(); // 빌런 이동 함수 불러오기
		zombie_move_func(); // 좀비 이동 함수 불러오기
		printf("\n");
		BSH3_2_train_shape_main_func(); // 기차 상태 불러오기
		printf("\n");

		// citizen_move_func() 으로 인해 시민이 움직였을 경우 or 안 움직였을 경우
		citizen_move_or_nomove_func();

		// villain_move_func() 으로 인해 빌런이 움직였을 경우 or 안 움직였을 경우
		villain_move_or_nomove_func();

		// zombie_move_func() 으로 인해 좀비가 움직였을 경우 or 안 움직였을 경우
		zombie_move_or_nomove_func(); // 홀수턴
		zombie_cannot_move_func(); // 짝수턴

		printf("\n");
		madongseok_move_func(); // 마동석 이동 결정 함수
		printf("\n");
		BSH3_2_train_shape_main_func(); // 기차 상태 출력 함수
		printf("\n\n");

		// 마동석 이동
		madongseok_move_main_func();

		printf("\n");

		printf("citizen does nothing.\n");
		// 시민이 탈출했을 때
		if (citizen == 1) {
			printf("GAME CLEAR! citizen safe !!\n");
			stage += 1;
			break;
		}

		// 좀비 공격으로 시민 또는 빌런 또는 마동석이 죽었을 때
		citizen_madongseok_villain_dead_func();

		// 좀비 공격으로 시민 또는 마동석이 죽었을 때
		if (citizen_dead == 1) {
			break;
		}
		else if (madongseok_dead == 1) {
			break;
		}

		// 마동석 행동 여부
		madongseok_action_yesorno_func();
		//
		phase += 1; // 턴을 1 증가시킨다.
	} // <- while 문 중괄호
	reset_func();
}

/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////


// --<< 부산헹(3) [ PDF 3-3 ] 추가된 전역 변수 >>--
int citizens_number; // 시민 생성 수
int citizens_number_select_list[LEN_MAX] = { 0 }; // 시민 생성 및 위치 배열
int citizens_aggro_list[LEN_MAX] = { 0 }; // 시민 어그로 배열
int citizens_move_list[LEN_MAX] = { 0 }; // 시민이 움직였는지 여부를 판단하는 배열
int citizens_safe_list[LEN_MAX] = { 0 }; // 시민이 탈출했을 때 +1 되는 배열
int citizens_safe_or_dead_list[LEN_MAX] = { 0 }; // 시민이 탈출했거나 죽었을 때 +1 올려서 더이상 시민들 움직임이 출력되지않게 하는 변수
int citizens_can_move = 0; // 시민들 이동 가능 여부
int citizens_count; // 시민 수 카운트 
int citizens_dead_count; // 시민이 죽었을 때 -1 되는 변수
int citizens_check = 0; // 시민이 움직였는지 체크하는 변수
int zombie_move_check = 0; // 좀비가 움직일 수 있는 체크하는 변수

// --<< 부산헹(3) [ PDF 3-3 ] 추가된 함수 정리 >>--

// 1) 시민들 생성 및 위치 함수
void citizens_make_func();
void citizens_make_func() {
	for (int i = 0; i < citizens_number; i++) {
		int same;
		citizens_aggro_list[i] = 1;
		while (1) {
			citizens_number_select_list[i] = rand() % (train_length - 7) + 2;
			same = 1; // 중복 여부 

			// 중복 검사
			for (int j = 0; j < i; j++) {
				if (citizens_number_select_list[i] == citizens_number_select_list[j]) {
					same = 0; // 중복이 있을 때
					break;
				}
			}

			// 중복이 없으면 while 문 탈출
			if (same == 1) {
				break;
			}
		}
	}
}

// 2) 시민들 이동 함수
void citizens_move_func();
void citizens_move_func() {
	for (int i = 0; i < citizens_number; i++) {
		int citizens_r = rand() % 101;
		citizens_move_list[i] = 0; // 시민이 움직이지 않았을 때의 배열
		if (citizens_safe_or_dead_list[i] == 0) { // 시민이 죽었거나 탈출했을 때 +1 되는 변수 및 배열 시민이 죽었으면 다음 조건문으로 안 감
			if (citizens_safe_list[i] != 1) {
				if (100 - p >= citizens_r) { // 시민이 움직일 때
					citizens_can_move = 1; // 시민이 움직일 수 있을 때 시민 이동 여부를 1로 정하기
					for (int j = 0; j < citizens_number; j++) {
						if (i != j && citizens_number_select_list[j] == citizens_number_select_list[i] - 1) { // 만약 시민 -1을 해야되는데 옆에 시민이 있을 때
							citizens_can_move = 0; // 시민 이동 여부를 0으로 정하기
							break;
						}
					}
					if (citizens_can_move == 1) { // 시민이 움직였을 때
						citizens_number_select_list[i] -= 1; // 시민 - 1
						citizens_aggro_list[i] += 1; // 시민 어그로 + 1 
						if (citizens_aggro_list[i] >= STM_MAX) {
							citizens_aggro_list[i] = STM_MAX;
						}
						citizens_move_list[i] = 1;
					}
					else {
						citizens_aggro_list[i] -= 1; // 시민 어그로 - 1
						if (citizens_aggro_list[i] <= STM_MIN) {
							citizens_aggro_list[i] = STM_MIN;
						}
					}
				}
				else { // 시민이 움직이지 않았을 때
					citizens_aggro_list[i] -= 1;
					if (citizens_aggro_list[i] <= STM_MIN) {
						citizens_aggro_list[i] = STM_MIN;
					}
				}
			}
		}
	}
}

// 3) citizens_move_func()으로 시민들이 움직였을 경우 or 안 움직였을 경우
void citizens_move_or_nomove_func();
void citizens_move_or_nomove_func() {
	for (int i = 0; i < citizens_number; i++) {
		if (citizens_number_select_list[i] != -1) {
			if (citizens_move_list[i] == 1) {
				// 이동 상태 출력
				printf("citizen %d: %d -> %d (aggro: %d -> %d)\n", i + 1, citizens_number_select_list[i] + 1, citizens_number_select_list[i], citizens_aggro_list[i] - 1, citizens_aggro_list[i]);
			}
			else {
				// 이동하지 못한 상태 출력
				printf("citizen %d stay: %d (aggro: %d -> %d)\n", i + 1, citizens_number_select_list[i], citizens_aggro_list[i] + 1, citizens_aggro_list[i]);
			}
		}
	}
}

// 4) 시민 어그로가 최대일 때
void citizen_aggro_if_max_func();
void citizen_aggro_if_max_func() {
	// 시민 어그로가 최대가 되면 최대 어그로로 고정.
	if (citizen_aggro >= AGGRO_MAX) {
		citizen_aggro = AGGRO_MAX;
	}
	else {
		citizen_aggro += 1;
	}
}

// 5) 시민 어그로가 최소일 때
void citizen_aggro_if_min_func();
void citizen_aggro_if_min_func() {
	// 시민 어그로가 최대가 되면 최대 어그로로 고정.
	if (citizen_aggro <= AGGRO_MIN) {
		citizen_aggro = AGGRO_MIN;
	}
	else {
		citizen_aggro -= 1;
	}
}
// 6) 시민 이동 (항상 좀비 옆옆에 고정적으로 시작하는 시민)
void citizen_0_move_func();
void citizen_0_move_func() {
	for (int i = 0; i < citizens_number; i++) {
		if (citizens_number_select_list[i] != citizen - 1) { // 시민 왼쪽에 시민들이 없을 때
			citizens_check = 0;
			break;
		}
		else { // 왼쪽에 시민이 있을 때
			citizens_check = 1;
		}
	}
	if (citizens_check == 0) { // 시민 왼쪽에 시민들이 없을 때
		if (100 - p >= r) { // 왼쪽 이동(O)
			pre_citizen = citizen;
			citizen -= 1;
			pre_citizen_aggro = citizen_aggro;
			citizen_aggro_if_max_func();
		}
		else { // 왼쪽 이동(X)
			pre_citizen = citizen;
			pre_citizen_aggro = citizen_aggro;
			citizen_aggro_if_min_func();
		}
	}
	else { // 왼쪽에 시민이 있을 때
		pre_citizen = citizen;
		pre_citizen_aggro = citizen_aggro;
		citizen_aggro_if_min_func();
	}
}

// 7) 시민들이 탈출했을 때 +1 되는 함수
void citizens_escape_func();
void citizens_escape_func() {
	for (int i = 0; i < citizens_number; i++) {
		if (citizens_number_select_list[i] == 1) {
			citizens_number_select_list[i] = -1;
			if (citizens_safe_or_dead_list[i] == 0) {
				citizens_safe_list[i] = 1;
				printf("citizen %d escape!\n", i+1);
				citizens_count -= 1;
				citizens_safe_or_dead_list[i] = 1;
			}
		}
		else {
			citizens_safe_list[i] = 0;
		}
	}
}

// 8) 시민이 좀비에게 공격당해서 죽었을 때
void citizens_dead_from_zombie_func(); 
void citizens_dead_from_zombie_func() {
	for (int i = 0; i < citizens_number; i++) {
		if (zombie - 1 == citizens_number_select_list[i]) {
			citizens_count -= 1;
			citizens_safe_or_dead_list[i] = 1; // 시민이 죽었을 때
			printf("citizen %d has been attacked by zombie\n", i+1);
			citizens_number_select_list[i] = -1; // 화면상에서 없애버리기
			citizens_dead_count -= 1;
		}
	}
}

// 9) 마동석 시민, 빌런, 좀비 초기 위치 설정 함수
void character_func();
void character_func() {
	madongseok = train_length - 2;
	zombie = train_length - 3;
	citizen = train_length - 5; // 시민
	pre_citizen = citizen;
	pre_zombie = zombie;
}

// 10) 기차 길이 (입력 및 예외처리) 함수 선언
void BSH3_3_train_length_func();
void BSH3_3_train_length_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		train_length_message_func();
		scanf_s("%d", &train_length);
		// 기차 길이가 15 ~ 50 사이일 때
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			break;
		}
	}
}

// 11) 기차 모양 (시민, 빌런, 좀비, 마동석 위치) 함수 선언 
void BSH3_3_train_shape_main_func();
void BSH3_3_train_shape_first_third_func();
void BSH3_3_train_shape_second_func();

// 11-1) 기차 첫째 줄, 셋째 줄
void BSH3_3_train_shape_first_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// 11-2) 기차 둘째 줄
void BSH3_3_train_shape_second_func() {
	for (int i = 0; i < train_length; i++) {
		int citizens_put_in = 0; // 시민들 자리에 왔을 때 +1을 해주기 위한 변수
		for (int j = 0; j < citizens_number; j++) {
			if (citizens_number_select_list[j] == i) {
				citizens_put_in = 1;
				break;
			}
		}
		if (citizens_put_in == 1) {
			printf("C");
		}
		// 기차의 처음과 끝을 '#' 으로 마무리
		else if (i == 0 || i == train_length - 1) {
			printf("#");
		}
		else if (i == citizen) { // 시민 1
			printf("C");
		}
		else if (i == zombie) {
			printf("Z");
		}
		else if (i == madongseok) {
			printf("M");
		}
		else {
			printf(" ");
		}

	}
	printf("\n");
}

// 11-3) 기차 함수 메인
void BSH3_3_train_shape_main_func() {
	BSH3_3_train_shape_first_third_func();
	BSH3_3_train_shape_second_func();
	BSH3_3_train_shape_first_third_func();
}

// 12) 좀비 -> 시민 이동 함수
void zombie_move_to_citizens_func();
void zombie_move_to_citizens_func() {
	// 마동석이 좀비 붙들기를 성공했을 때 (좀비 이동 불가)
	zombie_move_or_not_func();
	// 시민과 이미 인접해있을 때
	if (citizen_dead == 0) {
		if (zombie - 1 == citizen) {
			zombie = zombie;
		}
		else { // 민접해 있지 않을 때
			pre_zombie = zombie;
			zombie -= 1;
		}
	}
	else {
		for (int i = 0; i < citizens_number; i++) {
			if (zombie - 1 == citizens_number_select_list[i]) {
				zombie_move_check = 1;
				break;
			}
		}
		if (zombie_move_check == 1) { // 좀비와 시민이 인접해있을 때
			zombie = zombie;
		}
		else { // 좀비와 시민이 인접해있지 않을 때
			pre_zombie = zombie;
			zombie -= 1;
		}
	}
}

// 13) 부산헹(2) 좀비 이동 함수에서의 좀비와 시민 관계 코드
int zombie_move_to_citizen_func();
int zombie_move_to_citizen_func() {
	if (citizen_aggro > madongseok_aggro) { // 시민 어그로가 마동석 어그로보다 클 때
		zombie_move_citizen_func();

	}
	else if (madongseok_aggro > citizen_aggro) { // 마동석 어그로가 시민 어그로보다 클 때
		zombie_move_madongseok_func();

	}
	else { // 시민 어그로와 마동석 어그로가 같을 때
		zombie_move_citizen_func();
	}
}

// 14) 좀비 이동 함수
void zombie_move_from_citizens_func();
void zombie_move_from_citizens_func() {
	if (phase % 2 == 1) {
		if (zombie_move_or_not == 1) {
			if (citizen_dead == 1) {
				for (int i = 0; i < citizens_number; i++) {
					if (citizens_number_select_list[i] == zombie - 1) {
						if (citizens_aggro_list[i] > madongseok_aggro) {
							zombie_move_to_citizens_func();
							break;
						}
						else if (citizens_aggro_list[i] < madongseok_aggro) {
							zombie_move_madongseok_func();
							break;
						}
						else {
							zombie_move_to_citizens_func();
							break;
						}
					}
				}
			}
			else {
				zombie_move_to_citizen_func();
			}
		}
	}
}


// 15) 시민이 탈출했을 때
void citizen_escape_func();
void citizen_escape_func() {
	if (citizen == 1) {
		printf("citizen escape!!\n");
		citizens_count -= 1;
		citizen = -1;
	}
}

// 16) 남은 시민 수 출력
void citizens_howmany_message_func();
void citizens_howmany_message_func() {
	if (citizens_count != 0) {
		printf("%d citizen(s) alive(s).\n", citizens_count);
	}
}

// 17) 좀비가 시민 또는 마동석을 공격했을 때
void citizens_madongseok_dead_func();
void citizens_madongseok_dead_func() {
	if (citizen_dead == 1) { // 시민이 죽었을 때
		for (int i = 0; i < citizens_number; i++) {
			if (citizens_number_select_list[i] == zombie - 1 && zombie + 1 == madongseok) { // 좀비가 시민과 마동석과 인접할 때
				if (citizens_aggro_list[i] > madongseok_aggro) { // 시민어그로가 더 클 때
					citizens_count -= 1;
					citizens_safe_or_dead_list[i] = 1; // 시민이 죽었을 때
					printf("citizen %d has been attacked by zombie\n", citizens_number_select_list[i]);
					citizens_number_select_list[i] = -1; // 화면상에서 없애버리기
					citizens_dead_count -= 1;
				}
				else { // 마동석 어그로가 더 클 때
					madongseok_aggro_biggerthan_citizen_func();
					if (madongseok_stamina == STM_MIN) { // 마동석 체력이 STM_MIN 일 때
						madongseok_dead_message_func();
						madongseok_dead += 1;
					}
				}
			}
			else {
				zombie_attack_nobody_func();
			}
		}
	}
	else { // 시민이 살아있을 때
		citizen_madongseok_dead_func();
	}
}


// --<<<   부산헹(3) [ PDF 3-3. 스테이지3: 시민'들' ]  >>>--
void busanhang3_3_func();
void busanhang3_3_func() {
	printf("3_3\n");
	BSH3_3_train_length_func();

	// 시민 생성 수
	citizens_number = rand() % ((train_length / 2 + 1) - (train_length / 4)) + (train_length / 4); // 기차 길이가 20일 때 6 + 5 -> 5 ~ 10 명의 시민을 생성함.
	citizens_count = citizens_number + 1; // 시민 생성수 + 원래 있던 시민
	citizens_dead_count = citizens_number + 1; // 시민이 죽었을 때 -1 카운트 되는 변수

	citizens_make_func(); // 시민 생성 및 위치 함수
	character_func(); // * 마동석, 시민, 좀비 초기 위치 설정 *
	madongseok_stamina_func(); // 마동석 체력 (예외처리 O) 함수 불러오기
	probability_func(); // 확률 입력 (예외처리 O) 함수 불러오기
	printf("\n");
	
	BSH3_3_train_shape_main_func(); // 기차 초기 상태 불러오기
	printf("\n\n\n");

	// -< 메인 코드 메인 부분 >-
	while (1) {
		r = rand() % 101; // 시민 난수 출력
		k = rand() % 101; // 마동석 난수 출력
		
		citizens_move_func(); // 시민들 움직이는 함수 불러오기 
		citizen_0_move_func(); // 시민 움직이는 함수 불러오기
		zombie_move_from_citizens_func(); // 좀비 이동 함수 불러오기
		printf("\n");
		BSH3_3_train_shape_main_func(); // 기차 상태 불러오기
		printf("\n");

		// citizen_move_func으로 시민이 움직였을 때 or 안 움직였을 경우 
		citizen_move_or_nomove_func();
		//  citizens_move_func()으로 시민들이 움직였을 때 or 안 움직였을 경우
		citizens_move_or_nomove_func(); 
		// zombie_move_from_citizens_func() 으로 인해 좀비가 움직였을 경우 or 안 움직였을 경우
		zombie_move_or_nomove_func(); // 홀수턴 
		zombie_cannot_move_func(); // 짝수턴

		printf("\n");
		madongseok_move_func(); // 마동석 이동 결정 함수
		printf("\n");
		BSH3_3_train_shape_main_func(); // 기차 상태 출력 함수
		printf("\n\n");

		// 마동석 이동
		madongseok_move_main_func();

		printf("\n");

		// 시민이 탈출했을 때
		citizen_escape_func();
		
		// 시민들이 탈출했을 때
		citizens_escape_func();

		// 시민이 죽었을 때
		citizens_dead_from_zombie_func(); 

		// 남은 시민 수 출력
		citizens_howmany_message_func();

		if (citizens_count == 0) {
			if (citizens_dead_count == 0) {
				printf("GAME OVER! citizens all dead...\n");
				break;
			}
			else {
				printf("GAME CLEAR! %d citizen(s) alive(s)!\n", citizens_dead_count);
				stage += 1;
				break;
			}
		}

		// 좀비 공격으로 마동석이 죽었을 때
		citizens_madongseok_dead_func();
			if (madongseok_dead == 1) {
				printf("GAME OVER! madongseok dead...\n");
			break;
		}

		// 마동석 행동 여부
		madongseok_action_yesorno_func(); // 이 함수 새로 만들어야 됨
		//
		phase += 1; // 턴을 1 증가시킨다.
	}
	reset_func();
}

/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////
/////////// << 다음 스테이지 >> ///////////




// --<< 부산헹(3) [ PDF 3-4 ] 추가된 전역 변수 >>--
int citizens_change_zombie_list[LEN_MAX] = { 0 }; // 시민들이 좀비로 바뀌었을 때 +1 되는 변수
int citizen_change_zombie = 0; // 시민이 좀비로 바뀌었을 때 +1 되는 변수


// --<< 부산헹(3) [ PDF 3-4 ] 추가된 함수 정리 >>--

// 시민들과 좀비가 인접했을 때 강화좀비로 바뀌는 함수
void citizens_with_zombie_change_func();
void citizens_with_zombie_change_func() {
	for (int i = 0; i < citizens_number; i++) {
		if (citizens_change_zombie_list[i] == 0) {
			if (citizens_number_select_list[i] == zombie - 1) {
				citizens_change_zombie_list[i] = 1;
				printf("citizens %d turned into a zombie!", i + 1);
			}
		}
	}
}

// 시민과 좀비가 인접했을 때 강화좀비로 바뀌는 함수
void citizen_with_zombie_change_func();
void citizen_with_zombie_change_func() {
	if (citizen_change_zombie == 0) {
		if (citizen == zombie - 1) {
			citizen_change_zombie = 1;
			printf("citizen turned into a zombie!");
		}
	}
}

// 기차 상태 출력
void BSH3_4_train_shape_second_func();
void BSH3_4_train_shape_second_func() {
	for (int i = 0; i < train_length; i++) {
		int citizens_put_in = 0; // 시민들 자리에 왔을 때 +1을 해주기 위한 변수
		int citizens_put_in_zombie = 0; // 시민들이 좀비로 변해있는 경우 +1 해주는 변수
		for (int j = 0; j < citizens_number; j++) {
			if (citizens_number_select_list[j] == i) { // i가 citizens_number_select_list[j]일 때 citizens_put_in = 1로 만듦.
				citizens_put_in = 1;
				break;
			}
		}
		for (int j = 0; j < citizens_number; j++) {
			if (citizens_change_zombie_list[j] == 1) { // 시민이 좀비로 변해있는 경우 citizens_put_in_zombie 변수를 1로 바꿔줌
				citizens_put_in_zombie = 1;
			}
		}
		if (citizens_put_in == 1) {
			if (citizens_put_in_zombie == 1) { // 시민이 좀비가 되었을 때
				printf("Z");
			}
			else { // 시민이 좀비로 변하지 않았을 때
				printf("C");
			}
		}
		// 기차의 처음과 끝을 '#' 으로 마무리 
		else if (i == 0 || i == train_length - 1) { 
			printf("#"); 
		} 
		else if (i == citizen) { // 시민 1 
			if (citizen_change_zombie == 1) { // 시민이 좀비로 변했을 때
				printf("Z");
			}
			else { // 시민이 좀비로 변하지 않았을 때
				printf("C");
			}
		}
		else if (i == zombie) {
			printf("Z");
		}
		else if (i == madongseok) {
			printf("M");
		}
		else {
			printf(" ");
		}

	}
	printf("\n");
}

// 기차 상태 메인 함수
void BSH3_4_train_shape_main_func();
void BSH_3_4_train_shape_main_func() {
	BSH3_3_train_shape_first_third_func;
	BSH3_4_train_shape_second_func();
	BSH3_3_train_shape_first_third_func();
}

// 강화 좀비 이동 함수
void super_zombie_move_func();
void super_zombie_move_func() {

}







// --<<<   부산헹(3) [ PDF 3-4. 스테이지4: 변이 ]  >>>--

void busanhang3_4_func();
void busanhang3_4_func() {
	printf("Start Busanhang(3_4)!\n");
	BSH3_3_train_length_func();

	// 시민 생성 수
	citizens_number = rand() % ((train_length / 2 + 1) - (train_length / 4)) + (train_length / 4); // 기차 길이가 20일 때 6 + 5 -> 5 ~ 10 명의 시민을 생성함.
	citizens_count = citizens_number + 1; // 시민 생성수 + 원래 있던 시민
	citizens_dead_count = citizens_number + 1; // 시민이 죽었을 때 -1 카운트 되는 변수

	citizens_make_func(); // 시민 생성 및 위치 함수
	character_func(); // * 마동석, 시민, 좀비 초기 위치 설정 *
	madongseok_stamina_func(); // 마동석 체력 (예외처리 O) 함수 불러오기
	probability_func(); // 확률 입력 (예외처리 O) 함수 불러오기
	printf("\n");

	BSH3_3_train_shape_main_func(); // 기차 초기 상태 불러오기
	printf("\n\n\n");

	// -< 메인 코드 메인 부분 >-
	while (1) {
		r = rand() % 101; // 시민 난수 출력
		k = rand() % 101; // 마동석 난수 출력

		citizens_move_func(); // 시민들 움직이는 함수 불러오기 
		citizen_0_move_func(); // 시민 움직이는 함수 불러오기
		zombie_move_from_citizens_func(); // 좀비 이동 함수 불러오기
		printf("\n");
		BSH3_3_train_shape_main_func(); // 기차 상태 불러오기
		printf("\n");

		// citizen_move_func으로 시민이 움직였을 때 or 안 움직였을 경우 
		citizen_move_or_nomove_func();
		//  citizens_move_func()으로 시민들이 움직였을 때 or 안 움직였을 경우
		citizens_move_or_nomove_func();
		// zombie_move_from_citizens_func() 으로 인해 좀비가 움직였을 경우 or 안 움직였을 경우
		zombie_move_or_nomove_func(); // 홀수턴 
		zombie_cannot_move_func(); // 짝수턴

		printf("\n");
		madongseok_move_func(); // 마동석 이동 결정 함수
		printf("\n");
		BSH3_3_train_shape_main_func(); // 기차 상태 출력 함수
		printf("\n\n");

		// 마동석 이동
		madongseok_move_main_func();

		printf("\n");

		// 시민이 탈출했을 때
		citizen_escape_func();

		// 시민들이 탈출했을 때
		citizens_escape_func();

		// 시민이 죽었을 때
		citizens_dead_from_zombie_func();

		// 남은 시민 수 출력
		citizens_howmany_message_func();

		if (citizens_count == 0) {
			if (citizens_dead_count == 0) {
				printf("GAME OVER! citizens all dead...\n");
				break;
			}
			else {
				printf("GAME CLEAR! %d citizen(s) alive(s)!\n", citizens_dead_count);
				stage += 1;
				break;
			}
		}

		// 좀비 공격으로 마동석이 죽었을 때
		citizens_madongseok_dead_func();
		if (madongseok_dead == 1) {
			printf("GAME OVER! madongseok dead...\n");
			break;
		}

		// 마동석 행동 여부
		madongseok_action_yesorno_func(); // 이 함수 새로 만들어야 됨
		//
		phase += 1; // 턴을 1 증가시킨다.
	}
	
}

















































// --<< 메인 코드 작성 >>--
int main(void) {
	// -< 메인 코드 초기 부분 >-
	srand((unsigned int)time(NULL)); // 무작위 랜덤 난수
	// -< 메인 코드 메인 부분 >-
	//if (stage == 1) { // 부산헹 (2)
	//	busanhang2_func();
	//	if (stage == 2) { // 부산헹 (3-2)
	//		busanhang3_2_func();
	//		if (stage == 3) { // 부산헹 (3-3)
	//			busanhang3_3_func();
	//			if (stage == 4) { // 부산헹 (3-4)

	//			}
	//		}
	//	}
	//}
	//busanhang2_func(); // 부산헹(2) 함수 불러오기
	//busanhang3_2_func(); // 부산헹(3-2) 함수 불러오기 0
	//busanhang3_3_func();
	return 0;

} // <- int main(void) 중괄호
