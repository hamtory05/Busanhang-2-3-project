#include <stdio.h> 
#include <stdlib.h> 
  
// --<< 변수 정리 >>--  
  
// 1) 파라미터 
#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5 
#define PROB_MIN 10 // 확률 
#define PROB_MAX 90 
#define AGGRO_MIN 0 // 어그로 범위 
#define AGGRO_MAX 5
 
// 2) 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 3) 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 4) 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// 5) 전역 변수
int train_length; // 기차 길이
int madongseok_stamina; //마동석 체력 
int pre_madongseok_stamina; // 마동석 (전) 체력 상태
int probability, p; // 확률
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
int zombie_move_or_not; // 좀비가 마동석의 붙잡기에 따라 움직일지 안 움직일지 정하기

// --<< 필요한 함수 정의 >>--

// 0) 난수 함수 선언
int rand_func();
int rand_func() {
	int r = rand() % 101;
	return r;
}

// 1) 기차 길이 (입력 및 예외처리) 함수 선언
int train_length_func();
int train_length_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		printf("train length(%d ~ %d)>>", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
		// 기차 길이가 15 ~ 50 사이일 때
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			// * 마동석, 시민, 좀비 초기 위치 설정 *
			madongseok = train_length - 2;
			zombie = train_length - 3;
			citizen = train_length - 6;
			break;
		}
	}
}

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
			break;
		}
	}
}

// 4) 기차 상태 (첫째, 둘째, 셋째 줄) 함수 선언
int train_shape_first_third_func();
int train_shape_second_func();

// 4-1) 기차 첫째 줄, 셋째 줄
int train_shape_first_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

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

// 5) 마동석 이동 (입력 및 예외처리) 함수 선언
int madongseok_move_func();
int madongseok_move_func() {
	// 유효한 값이 입력될 때까지 무한반복
	while (1) {
		printf("madongseok move(0:stay, 1:left)>>");
		scanf_s("%d", &madongseok_move);
		// 마동석 이동이 0 또는 1일 때 무한반복 나오기
		if (madongseok_move == 1 || madongseok_move == 0) {
			break;
		}
	}
}

// 6) 시민(어그로 포함) 좀비 이동 함수 선언 
int citizen_move_main_func(); // 시민 메인 이동 함수
int zombie_move_main_func(); // 좀비 메인 이동 함수
int citizen_move_func(); // 시민 이동 함수
int citizen_aggro_max_func(); // 시민 최대 어그로 (예외처리) 함수
int citizen_move_left_func(); // 시민 이동 (왼쪽 한칸) 함수
int citizen_move_stay_func(); // 시민 이동 (왼쪽 한칸 X) 함수
int zombie_move_func(); // 좀비 이동 함수
int zombie_attack_func(); // 좀비 공격 행동 규칙 함수
int zombie_move_or_not_func(); //  마동석이 좀비 붙들기에 성공했을때 or 실패했을 때의 좀비 이동 상태 함수
int zombie_move_citizen_func(); // 좀비 -> 시민 이동 함수
int zombie_move_madongseok_func(); // 좀비 -> 마동석 이동 함수


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
	printf("citizen: %d -> %d (aggro: %d -> %d)\n", pre_citizen, citizen, pre_citizen_aggro, citizen_aggro);
}

// 6-2) 시민 최대 어그로 (예외처리) 함수
int citizen_aggro_max_func() {
	pre_citizen_aggro = citizen_aggro;
	if (citizen_aggro <= AGGRO_MIN) {
		citizen_aggro = 0;
	}
	else {
		citizen_aggro -= 1;
	}
	printf("citizen: stay %d (aggro: %d -> %d)", citizen, pre_citizen_aggro, citizen_aggro);
}
// 6-3) 시민 이동 (왼쪽 한칸 X) 함수
int citizen_move_stay_func() {
	citizen_aggro_max_func(); 
}

// 6-4) 시민 이동 메인 함수 
int citizen_move_func() {
	if (p - 100 > rand_func()) {
		citizen_move_left_func();
	}
	else {
		citizen_move_stay_func();
	}
}

// 6-5) 마동석이 좀비 붙들기에 성공했을때 or 실패했을 때의 좀비 이동 상태 함수
int zombie_move_or_not_func() {
	if (zombie_move_or_not == 0) { // 좀비 붙들기에 성공했을 때
		phase -= 1;
	}
	else { // 좀비 붙들기에 실패했을 때
		phase = phase;
	}
	return phase;
}
// 6-5) 좀비 -> 시민 이동 함수
int zombie_move_citizen_func() {
	zombie -= 1;
	// 마동석이 좀비 붙들기를 성공했을 때 (좀비 이동 불가)
	zombie_move_or_not_func(); 
	// 시민과 이미 민접해 있을 때
	if (zombie - 1 == citizen) {
		zombie = zombie;
	}
	else { // 민접해 있지 않을 때
		zombie -= 1;
	}
}
// 6-6) 좀비 -> 마동석 이동 함수
int zombie_move_madongseok_func() {
	// 마동석이 좀비 붙들기를 성공했을 때 (좀비 이동 불가)
	zombie_move_or_not_func(); 
	// 마동석과 이미 민접해 있을 때
	if (zombie + 1 == madongseok) {
		zombie = zombie;
	}
	else { // 민접해 있지 않을 때
		zombie -= 1;
	}
}

// 6-7) 좀비 이동 함수
int zombie_move_func() {
	if (phase % 2 == 0) { // 턴이 짝수일 때 (즉, 2턴마다)
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

// 6-8) 좀비 공격 함수
int zombie_attack_func() {
	
}

// 6-8) 시민 메인 이동 함수
int citizen_move_main_func() {
	citizen_move_func();
}

// 6-9) 좀비 메인 이동 함수
int zombie_move_main_func() {
	if (zombie_move_func()) {

	}
}

// 7) 마동석 행동 함수 선언 
int madongseok_action_func(); // 마동석 행동 메인 함수
int madongseok_action_0_func(); // 마동석 행동이 0을 입력 받았을 때의 함수
int madongseok_action_1_func(); // 마동석 행동이 1을 입력 받았을 때의 함수
int madongseok_action_2_func(); // 마동석 행동이 2를 입력 받았을 때의 함수
int madongseok_action_withzombie_func(); // 마동석이 좀비와 인접한 경우의 함수
int madongseok_aggro_max_func(); // 마동석 어그로가 최대를 넘지 않기 위한 함수
int madongseok_action_start_func(); // 마동석 행동 입력 받았을 때 실행시킬 함수

// 7-1) 마동석 휴식 함수 (0을 입력 받았을 때)
int madongseok_action_0_func() {
	printf("madongseok rests...\n");
	pre_madongseok_aggro = madongseok_aggro;
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_aggro -= 1;
	madongseok_stamina += 1;
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d\n", madongseok, pre_madongseok_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

// 7-2) 마동석 최대 어그로 및 스테미나 (2번 입력 행동부분 예외처리) 함수 선언
int madongseok_aggro_max_func() {
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro += 2;
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_stamina -= 1;
	// 마동석 어그로가 최대 어그로가 되었을 때
	if (madongseok_aggro >= AGGRO_MAX) {
		madongseok_aggro = 5;
	}
	else {
		madongseok_aggro += 1;
	}
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)", madongseok, pre_madongseok_aggro, madongseok_aggro);
}
// 7-3) 마동석 도발 함수 (1을 입력 받았을 때)
int madongseok_action_1_func() {
	printf("madongseok provoked zomebie...\n");
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro = AGGRO_MAX;
	printf("madongseok : %d (aggro: %d -> %d, stamina: %d\n", madongseok, pre_madongseok_aggro, madongseok_aggro, madongseok_stamina);
}

// 7-4) 마동석 붙들기 함수 (2를 입력 받았을 때)
int madongseok_action_2_func() {
	if (100 - p > rand()) {
		zombie_move_or_not = 0; // 마동석이 좀비 붙들기에 성공했을 때 좀비가 못 움직이게 하기 위한 변수 
		printf("madongseok pulled zombie... Next turn, it can't move\n");
		madongseok_aggro_max_func();
	}
	else {
		zombie_move_or_not = 1; // 마동석이 좀비 붙들기에 실패했을 때 좀비가 움직이게 하기 위한 변수
		printf("madongseok failed to pull zombie");
		madongseok_aggro_max_func(); 
	}
}

// 7-5) 마동석 행동 입력 받았을 때 실행시킬 함수
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
// 7-6) 마동석 (좀비와 인접한 경우) 행동 규칙 함수
int madongseok_action_withzombie_func() {
	while (1) {
		printf("madongseok action(0. rest, 1.provoke, 2.pull)>>");
		scanf_s("%d", &madongseok_action);
		if (madongseok_action > 2 && madongseok_action < 0) {
			continue;
		}
		else {
			madongseok_action_start_func();
			break;
		}
	}
}

// 7-7) 마동석 행동 메인 함수 
int madongseok_action_func() {
	printf("citizen does nothing.");
	printf("zombie attacked nobody.");
	// 유효한 값이 입력될 때까지 무한 반복
	while (1) {
		printf("madongseok action(0.rest, 1.provoke)>>");
		scanf_s("%d", &madongseok_action);
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



// --<< 메인 코드 작성 >>--
int main(void) {
	srand((unsigned int)time(NULL)); 
} 
