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

// [ PDF 2-1 ~ 2.4에 쓰이는 변수들 ]
// 5) 전역 변수
int train_length; // 기차 길이
int madongseok_stamina; //마동석 체력 
int pre_madongseok_stamina; // 마동석 (전) 체력 상태
int probability; // 확률
int p; // 확률 (줄임말)
int citizen; // 시민
int pre_citizen; // 시민 (전) 상태 
int zombie; // 좀비
int pre_zombie; // 좀비 (전) 상태
int madongseok; // 마동석
int pre_madongseok; // 마동석 (전) 상태
int citizen_aggro = 1; // 시민 어그로
int pre_citizen_aggro; // 시민 (전) 어그로
int madongseok_aggro = 1; // 마동석 어그로
int pre_madongseok_aggro; // 마동석 (전) 어그로
int madongseok_move; // 마동석 이동
int phase = 1; // 턴, 페이즈
int madongseok_action; // 마동석 행동
int zombie_move_or_not = 1; // 좀비가 마동석의 붙잡기에 따라 움직일지 안 움직일지 정하기
int r, k;
// --<< 필요한 함수 정의 >>--

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 1) 기차 길이 (입력 및 예외처리) 함수 선언
int train_length_func();
int train_length_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		printf("train length(%d ~ %d)>>", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
		// 기차 길이가 15 ~ 50 사이일 때
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			break;
		}
	}
	// * 마동석, 시민, 좀비 초기 위치 설정 *
	madongseok = train_length - 2;
	zombie = train_length - 3;
	citizen = train_length - 6;
	pre_citizen = citizen;
	pre_zombie = zombie;
	pre_madongseok = madongseok;
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 2) 마동석 체력 (입력 및 예외처리) 함수 선언
int madongseok_stamina_func();
int madongseok_stamina_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		printf("madongseok stamina(%d ~ %d)>>", STM_MIN, STM_MAX);
		scanf_s("%d", &madongseok_stamina);
		// 마동석 체력이 0~5 사이일 때
		if (madongseok_stamina >= STM_MIN && madongseok_stamina <= STM_MAX) {
			break;
		}
	} 
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 3) 확률 (입력 및 예외처리) 함수 선언
int probability_func();
int probability_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		printf("percentile probability 'p'(%d ~ %d)>>", PROB_MIN, PROB_MAX);
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
int train_shape_first_third_func();
int train_shape_second_func();
int train_shape_main_func();

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 4-1) 기차 첫째 줄, 셋째 줄
int train_shape_first_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// [ PDF 2-2 부산헹 (1)에서 수정 ]
// 4-2) 기차 둘째 줄
int train_shape_second_func() {
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
int train_shape_main_func() {
	train_shape_first_third_func();
	train_shape_second_func();
	train_shape_first_third_func();
}
// [ PDF 2-3 < 이동 > &2 - 3 < 이동 > :예외처리 ]
// 5) 마동석 이동 (입력 및 예외처리) 함수 선언
int madongseok_move_func();
int madongseok_move_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		// 좀비가 마동석 옆에 있을 때
		if (zombie + 1 == madongseok) {
			printf("madongseok move(0:stay)>>");
			scanf_s("%d", &madongseok_move);
			// 마동석 이동이 0일 때 무한반복 나오기
			if (madongseok_move == 0) {
				return madongseok_move;
				break;
			}
		}
		else {
			// 좀비가 마동석 옆에 없을 때
			printf("madongseok move(0:stay, 1:left)>>");
			scanf_s("%d", &madongseok_move);
			// 마동석 이동이 0 또는 1일 때 무한반복 나오기
			if (madongseok_move == 1) {
				madongseok -= 1;
				return madongseok_move;
				break;
			}
			else {
				return madongseok_move;
			}
		}
	}
}

// [ PDF 2-2 ~ 2-4에 쓰이는 함수들 모음 ]
// 6) 시민(어그로 포함) 좀비 이동 함수 선언 
int citizen_move_func(); // 시민 이동 함수
int citizen_aggro_max_func(); // 시민 최대 어그로 (예외처리) 함수
int citizen_move_left_func(); // 시민 이동 (왼쪽 한칸) 함수
int citizen_move_stay_func(); // 시민 이동 (왼쪽 한칸 X) 함수
int citizen_move_or_nomove_func(); // 시민이 citizen_move_func() 으로 움직였을 때 또는 안 움직였을 때
int zombie_move_func(); // 좀비 이동 함수
int zombie_move_or_not_func(); //  마동석이 좀비 붙들기에 성공했을때 or 실패했을 때의 좀비 이동 상태 함수
int zombie_move_or_nomove_func(); // 좀비가 zombie_move_func() 으로 움직였을 때 또는 안 움직였을 때
int zombie_move_citizen_func(); // 좀비 -> 시민 이동 함수
int zombie_move_madongseok_func(); // 좀비 -> 마동석 이동 함수
int madongseok_aggro_biggerthan_citizen_func(); // 마동석 어그로가 시민 어그로보다 클 때 

// [ PDF 2-3 <이동> & 2-3 <이동>: 예외처리 ]
// 6-1) 시민 이동 (왼쪽 한칸) 함수
int citizen_move_left_func() {
	pre_citizen = citizen;
	citizen -= 1;
	pre_citizen_aggro = citizen_aggro;
	// 시민 어그로가 최대가 되면 최대 어그로로 고정.
	if (citizen_aggro >= AGGRO_MAX) {
		citizen_aggro = 5;
	}
	else {
		citizen_aggro += 1;
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-2) 시민 최대 어그로 (예외처리) 함수
int citizen_aggro_max_func() {
	pre_citizen_aggro = citizen_aggro;
	if (citizen_aggro <= AGGRO_MIN) {
		citizen_aggro = 0;
	}
	else {
		citizen_aggro -= 1;
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-3) 시민 이동 (왼쪽 한칸 X) 함수
int citizen_move_stay_func() {
	citizen_aggro_max_func(); 
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-4) 시민 이동 메인 함수 
int citizen_move_func() {
	if (100 - p >= r) {
		citizen_move_left_func();
	}
	else {
		citizen_move_stay_func();
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-5) 마동석 어그로가 시민 어그로보다 클 때의 함수
int madongseok_aggro_biggerthan_citizen_func() {
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_stamina -= 1;
	printf("zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina : %d -> %d)\n", citizen_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-6) 시민이 citizen_move_or_nomove_func() 으로 인해 움직였을 때 또는 안 움직였을 때
int citizen_move_or_nomove_func() {
	if (citizen == pre_citizen) { // 시민이 움직이지 않았을 때
		if (citizen_aggro == AGGRO_MIN) { // 시민 어그로가 0일 때
			printf("citizen: stay %d (aggro: %d -> %d)\n", citizen, pre_citizen_aggro, citizen_aggro);
		}
		else { // 시민 어그로가 0이 아닐 때
			printf("citizen: stay %d (aggro: %d -> %d)\n", citizen, pre_citizen_aggro, citizen_aggro);
		}
	}
	else { // 시민이 움직였을 때
		printf("citizen: %d -> %d (aggro: %d -> %d)\n", pre_citizen, citizen, pre_citizen_aggro, citizen_aggro);
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-7) 좀비 이동 함수
int zombie_move_func() {
	if (phase % 2 == 1) { // 턴이 홀수일 때 (즉, 2턴마다)
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

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ]
// 6-8) zombie_move_or_nomove_func으로 좀비가 움직였을 때 또는 안 움직였을 때
int zombie_move_or_nomove_func() {
	if (zombie_move_or_not == 1) { // 마동석이 붙들기 함수에서 실패했을 때
		if (zombie == pre_zombie) { // 좀비가 그 자리에 있을 때
			printf("zombie: stay %d\n", zombie);
		}
		else { // 좀비가 움직였을때
			printf("zombie: %d -> %d\n", pre_zombie, zombie);
		}
	}
	else { // 마동석이 붙들기 함수에서 성공했을 때
		printf("zombie: stay %d\n", zombie);
	}
}

// [ PDF 2-4 <행동> & 2-4 <행동> : 예외처리 ]
// 6-9) 마동석이 좀비 붙들기에 성공했을때 or 실패했을 때의 좀비 이동 상태 함수
int zombie_move_or_not_func() {
	if (zombie_move_or_not == 0) { // 좀비 붙들기에 성공했을 때
		phase -= 1;
	}
	else { // 좀비 붙들기에 실패했을 때
		phase = phase;
	}
	return phase;
}


// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ], [ PDF 2-4 <행동> & 2-4 <행동> : 예외처리 ]
// 6-10) 좀비 -> 마동석 이동 함수
int zombie_move_madongseok_func() {
	// 마동석이 좀비 붙들기를 성공했을 때 (좀비 이동 불가)
	zombie_move_or_not_func();
	// 마동석과 이미 민접해 있을 때
	if (zombie + 1 == madongseok) {
		zombie = zombie;
	}
	else { // 민접해 있지 않을 때
		pre_zombie = zombie;
		zombie -= 1;
	}
}

// [ PDF 2-3 < 이동 > & 2-3 < 이동 > :예외처리 ], [ PDF 2-4 <행동> & 2-4 <행동> : 예외처리 ]
// 6-9) 좀비 -> 시민 이동 함수
int zombie_move_citizen_func() {
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
int madongseok_action_func(); // 마동석 행동 메인 함수
int madongseok_action_0_func(); // 마동석 행동이 0을 입력 받았을 때의 함수
int madongseok_action_1_func(); // 마동석 행동이 1을 입력 받았을 때의 함수
int madongseok_action_2_func(); // 마동석 행동이 2를 입력 받았을 때의 함수
int madongseok_action_withzombie_func(); // 마동석이 좀비와 인접한 경우의 함수
int madongseok_aggro_max_func(); // 마동석 어그로가 최대를 넘지 않기 위한 함수
int madongseok_action_start_func(); // 마동석 행동 입력 받았을 때 실행시킬 함수
int madongseok_move_0_func(); // 마동석 이동이 0을 입력 받았을 때의 함수
int madongseok_move_1_func(); // 마동석 이동이 1을 입력 받았을 때의 함수
int madongseok_action_yesorno_func(); // 마동석 행동 여부 함수

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-1) 마동석 (action) 휴식 함수 (0을 입력 받았을 때)
int madongseok_action_0_func() {
	printf("madongseok rests...\n");
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
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-2) 마동석 (move) 휴식 함수 (0을 입력받았을 때)
int madongseok_move_0_func() { 
	madongseok_aggro -= 1;
	if (madongseok_aggro <= AGGRO_MIN) {
		madongseok_aggro = AGGRO_MIN;
	}
	else {

	}
	printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", madongseok, madongseok_aggro, madongseok_stamina);
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-3) 마동석 (move) 왼쪽으로 이동 했을 때 함수 (1을 입력했을 때) 
int madongseok_move_1_func() {
	madongseok_aggro += 1;
	if (madongseok_aggro >= AGGRO_MAX) {
		madongseok_aggro = AGGRO_MAX;
	}
	else {

	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-4) 마동석 최대 어그로 및 스테미나 (2번 입력 행동부분 예외처리) 함수 선언
int madongseok_aggro_max_func() {
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
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

// [ PDF 2-4 <행동> & <행동> : 예외처리
// 7-5) 마동석 도발 함수 (1을 입력 받았을 때) ]
int madongseok_action_1_func() {
	printf("madongseok provoked zomebie...\n");
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro = AGGRO_MAX;
	printf("madongseok : %d (aggro: %d -> %d, stamina: %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, madongseok_stamina);
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-6) 마동석 붙들기 함수 (2를 입력 받았을 때)
int madongseok_action_2_func() {
	if (100 - p >= k) {
		zombie_move_or_not = 0; // 마동석이 좀비 붙들기에 성공했을 때 좀비가 못 움직이게 하기 위한 변수 
		printf("madongseok pulled zombie... Next turn, it can't move\n");
		madongseok_aggro_max_func();
		zombie_move_or_not_func();
	}
	else {
		zombie_move_or_not = 1; // 마동석이 좀비 붙들기에 실패했을 때 좀비가 움직이게 하기 위한 변수
		printf("madongseok failed to pull zombie\n");
		madongseok_aggro_max_func();
		zombie_move_or_not_func();
	}
}

// [ PDF 2-4 <행동> & <행동> : 예외처리 ]
// 7-7) 마동석 행동 입력 받았을 때 실행시킬 함수
int madongseok_action_start_func() {
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
// 7-8) 마동석 (좀비와 인접한 경우) 행동 규칙 함수
int madongseok_action_withzombie_func() {
	while (1) {
		printf("madongseok action(0. rest, 1.provoke, 2.pull)>>");
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
// 7-9) 마동석 행동 메인 함수 
int madongseok_action_func() {
	// 유효한 값이 입력될 때까지 무한 반복
	while (1) {
		printf("madongseok action(0.rest, 1.provoke)>>");
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

// 마동석 행동 여부 함수
int madongseok_action_yesorno_func() {
	if (madongseok == zombie + 1) { // 마동석이 좀비와 인접할 때
		madongseok_action_withzombie_func(); // 마동석 행동 함수 불러오기
	}
	else { // 마동석이 좀비와 인접하지 않을 때
		madongseok_action_func(); // 마동석 행동 함수 불러오기
	}
}

// --<< 메인 코드 작성 >>--
int main(void) {
	// -< 메인 코드 초기 부분 >-
	srand((unsigned int)time(NULL)); // 무작위 랜덤 난수
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
		zombie_move_or_nomove_func();

		printf("\n");
		madongseok_move_func(); // 마동석 이동 결정 함수
		printf("\n");
		train_shape_main_func(); // 기차 상태 출력 함수
		printf("\n\n");

		// 마동석 이동
		if (madongseok_move == 0) { // 0을 입력받았을 때
			madongseok_move_0_func();
		}
		else { // 1를 입력 받았을 때
			madongseok_move_1_func();
		}

		printf("\n");

		printf("citizen does nothing.\n");
		// 시민이 탈출했을 때
		if (citizen == 1) {
			printf("GAME CLEAR! citizen safe !!");
			break;
		}

		// 좀비 공격 여부
		if (zombie - 1 == citizen && zombie + 1 == madongseok) { // 좀비가 시민과 마동석 둘 다 인접해 있을 때
			if (citizen_aggro > madongseok_aggro) { // 시민의 어그로가 더 클 때
				printf("GAME OVER! citizen dead...");
				break;
			}
			else { // 마동석의 어그로가 더 클 때
				madongseok_aggro_biggerthan_citizen_func();
				if (madongseok_stamina == STM_MIN) { // 마동석 체력이 STM_MIN 일 때
					printf("GAME OVER! madongseok_dead...");
					break;
				}
			}
		}
		else if (zombie - 1 == citizen || zombie + 1 == madongseok) { // 좀비가 시민 또는 마동석 둘 중 한명에게 인접해있을 때
			if (zombie - 1 == citizen) { // 좀비와 시민이 인접해있을 때
				printf("GAME OVER! citizen dead...");
				break;
			}
			else { // 좀비와 마동석이 인접해있을 때
				if (madongseok_stamina == STM_MIN) { // 마동석 체력이 STM_MIN 일 때
					printf("GAME OVER! madongseok dead...");
					break;
				}
			}
		}
		else { // 둘 다 인접해있지 않을 때
			printf("zombie attacked nobody.\n");
		}

		// 마동석 행동 여부
		madongseok_action_yesorno_func();
		//
		phase += 1; // 턴을 1 증가시킨다.
	} // <- while 문 중괄호
	return 0;
} // <- int main(void) 중괄호
