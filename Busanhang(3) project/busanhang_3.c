#include <stdio.h> 
#include <stdlib.h> 

// --<< ���� ���� >>--  

// [ PDF 2-2. �λ���(1)���� ���� ]
// 1) �Ķ���� 
#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define STM_MIN 0 // ������ ü��
#define STM_MAX 5 
#define PROB_MIN 10 // Ȯ�� 
#define PROB_MAX 90 
#define AGGRO_MIN 0 // ��׷� ���� 
#define AGGRO_MAX 5

// [ PDF 2-2. �λ���(1)���� ���� ]
// 2) ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// [ PDF 2-2. �λ���(1)���� ���� ]
// 3) ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// [ PDF 2-2. �λ���(1)���� ���� ]
// 4) ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// [ PDF 2-1 ~ 3-4�� ���̴� ������ ]
// 5) ���� ����
int train_length; // ���� ����
int madongseok_stamina; //������ ü�� 
int pre_madongseok_stamina; // ������ (��) ü�� ����
int probability; // Ȯ��
int p; // Ȯ�� (���Ӹ�)
int citizen_1; // �ù� 1
int pre_citizen_1; // �ù� 1 (��) ���� 
int zombie; // ����
int pre_zombie; // ���� (��) ����
int madongseok; // ������
int pre_madongseok; // ������ (��) ����
int citizen_1_aggro = 1; // �ù� 1 ��׷�
int pre_citizen_1_aggro; // �ù� 1 (��) ��׷�
int madongseok_aggro = 1; // ������ ��׷�
int pre_madongseok_aggro; // ������ (��) ��׷�
int madongseok_move; // ������ �̵�
int phase = 1; // ��, ������
int madongseok_action; // ������ �ൿ
int zombie_move_or_not = 1; // ���� �������� ����⿡ ���� �������� �� �������� ���ϱ�
int r, k;
int villain; // ����
int pre_villain; // ���� (��) ����
int j; // ���� ���� 
int villain_aggro; // ���� ��׷�
int villain_pre_aggro; // ���� (��) ��׷� ����

// --<< �ʿ��� �Լ� ���� >>--

// [ PDF 2-2 �λ��� (1)���� ���� ]
// 1) ���� ���� (�Է� �� ����ó��) �Լ� ����
int train_length_func();
int train_length_func() {
	// ��ȿ�� ���� �Էµ� ������ ���ѹݺ�
	while (1) {
		printf("train length(%d ~ %d)>>", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
		// ���� ���̰� 15 ~ 50 ������ ��
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			break;
		}
	}
	// * ������, �ù� 1, ���� �ʱ� ��ġ ���� *
	madongseok = train_length - 2;
	zombie = train_length - 3;
	citizen_1 = train_length - 6;
	pre_citizen_1 = citizen_1;
	pre_zombie = zombie;
	pre_madongseok = madongseok;
}

// [ PDF 2-2 �λ��� (1)���� ���� ]
// 2) ������ ü�� (�Է� �� ����ó��) �Լ� ����
int madongseok_stamina_func();
int madongseok_stamina_func() {
	// ��ȿ�� ���� �Էµ� ������ ���ѹݺ�
	while (1) {
		printf("madongseok stamina(%d ~ %d)>>", STM_MIN, STM_MAX);
		scanf_s("%d", &madongseok_stamina);
		// ������ ü���� 0~5 ������ ��
		if (madongseok_stamina >= STM_MIN && madongseok_stamina <= STM_MAX) {
			break;
		}
	}
}

// [ PDF 2-2 �λ��� (1)���� ���� ]
// 3) Ȯ�� (�Է� �� ����ó��) �Լ� ����
int probability_func();
int probability_func() {
	// ��ȿ�� ���� �Էµ� ������ ���ѹݺ�
	while (1) {
		printf("percentile probability 'p'(%d ~ %d)>>", PROB_MIN, PROB_MAX);
		scanf_s("%d", &probability);
		p = probability;
		// Ȯ���� 10 ~ 90 ������ ��
		if (p >= PROB_MIN && p <= PROB_MAX) {
			return p;
			break;
		}
	}
}

// [ PDF 2-2 �λ��� (1)���� ���� ]
// 4) ���� ���� (ù°, ��°, ��° ��) �Լ� ����
int train_shape_first_third_func();
int train_shape_second_func();
int train_shape_main_func();

// [ PDF 2-2 �λ��� (1)���� ���� ]
// 4-1) ���� ù° ��, ��° ��
int train_shape_first_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// [ PDF 2-2 �λ��� (1)���� ���� ]
// 4-2) ���� ��° ��
int train_shape_second_func() {
	for (int i = 0; i < train_length; i++) {
		// ������ ó���� ���� '#' ���� ������
		if (i == 0 || i == train_length - 1) {
			printf("#");
		}
		else if (i == citizen_1) {
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

// [ PDF 2-2 �λ��� (1)���� ���� ]
// 4-3) ���� (1 ~ 3 ��) ���� �Լ�
int train_shape_main_func() {
	train_shape_first_third_func();
	train_shape_second_func();
	train_shape_first_third_func();
}
// [ PDF 2-3 < �̵� > &2 - 3 < �̵� > :����ó�� ]
// 5) ������ �̵� (�Է� �� ����ó��) �Լ� ����
int madongseok_move_func();
int madongseok_move_func() {
	// ��ȿ�� ���� �Էµ� ������ ���ѹݺ�
	while (1) {
		// ���� ������ ���� ���� ��
		if (zombie + 1 == madongseok) {
			printf("madongseok move(0:stay)>>");
			scanf_s("%d", &madongseok_move);
			// ������ �̵��� 0�� �� ���ѹݺ� ������
			if (madongseok_move == 0) {
				return madongseok_move;
				break;
			}
		}
		else {
			// ���� ������ ���� ���� ��
			printf("madongseok move(0:stay, 1:left)>>");
			scanf_s("%d", &madongseok_move);
			// ������ �̵��� 0 �Ǵ� 1�� �� ���ѹݺ� ������
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

// [ PDF 2-2 ~ 2-4�� ���̴� �Լ��� ���� ]
// 6) �ù�(��׷� ����) ���� �̵� �Լ� ���� 
int citizen_move_func(); // �ù� �̵� �Լ�
int citizen_aggro_max_func(); // �ù� �ִ� ��׷� (����ó��) �Լ�
int citizen_move_left_func(); // �ù� �̵� (���� ��ĭ) �Լ�
int citizen_move_stay_func(); // �ù� �̵� (���� ��ĭ X) �Լ�
int zombie_move_func(); // ���� �̵� �Լ�
int zombie_move_or_not_func(); //  �������� ���� �ٵ�⿡ ���������� or �������� ���� ���� �̵� ���� �Լ�
int zombie_move_citizen_func(); // ���� -> �ù� �̵� �Լ�
int zombie_move_madongseok_func(); // ���� -> ������ �̵� �Լ�
int madongseok_aggro_biggerthan_citizen_villain_func(); // ������ ��׷ΰ� �ù� ��׷κ��� Ŭ ��

// [ PDF 2-3 <�̵�> & 2-3 <�̵�>: ����ó�� ]
// 6-1) �ù� �̵� (���� ��ĭ) �Լ�
int citizen_move_left_func() {
	pre_citizen_1 = citizen_1;
	citizen_1 -= 1;
	pre_citizen_1_aggro = citizen_1_aggro;
	// �ù� ��׷ΰ� �ִ밡 �Ǹ� �ִ� ��׷η� ����.
	if (citizen_1_aggro >= AGGRO_MAX) {
		citizen_1_aggro = 5;
	}
	else {
		citizen_1_aggro += 1;
	}
}

// [ PDF 2-3 < �̵� > & 2-3 < �̵� > :����ó�� ]
// 6-2) �ù� �ִ� ��׷� (����ó��) �Լ�
int citizen_aggro_max_func() {
	pre_citizen_1_aggro = citizen_1_aggro;
	if (citizen_1_aggro <= AGGRO_MIN) {
		citizen_1_aggro = 0;
	}
	else {
		citizen_1_aggro -= 1;
	}
}

// [ PDF 2-3 < �̵� > & 2-3 < �̵� > :����ó�� ]
// 6-3) �ù� �̵� (���� ��ĭ X) �Լ�
int citizen_move_stay_func() {
	citizen_aggro_max_func();
}

// [ PDF 2-3 < �̵� > & 2-3 < �̵� > :����ó�� ]
// 6-4) �ù� �̵� ���� �Լ� 
int citizen_move_func() {
	if (100 - p >= r) {
		citizen_move_left_func();
	}
	else {
		citizen_move_stay_func();
	}
}

// [ PDF 2-3 < �̵� > & 2-3 < �̵� > :����ó�� ]
// 6-5) ������ ��׷ΰ� �ù� ��׷κ��� Ŭ �� �Ǵ� ������ ��׷κ��� Ŭ ���� �Լ�
int madongseok_aggro_biggerthan_citizen_villain_func() {
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_stamina -= 1;
	if (madongseok_aggro > citizen_1_aggro) { // �ù� ��׷κ��� Ŭ ��
		printf("zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina : %d -> %d)\n", citizen_1_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
	}
	else { // ������ ��׷ΰ� �� Ŭ ��
		printf("zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina : %d -> %d)\n", villain_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
	}
}

// [ PDF 2-3 < �̵� > & 2-3 < �̵� > :����ó�� ]
// 6-6) ���� �̵� �Լ�
int zombie_move_func() {
	if (phase % 2 == 1) { // ���� Ȧ���� �� (��, 2�ϸ���)
		if (citizen_1_aggro > madongseok_aggro) { // �ù� ��׷ΰ� ������ ��׷κ��� Ŭ ��
			zombie_move_citizen_func();

		}
		else if (madongseok_aggro > citizen_1_aggro || madongseok_aggro > villain_aggro) { // ������ ��׷ΰ� �ù� ��׷κ��� Ŭ �� �Ǵ� ���� ��׷κ��� Ŭ ��
			zombie_move_madongseok_func();

		}
		else { // �ù� ��׷ο� ������ ��׷ΰ� ���� �� �Ǵ� ���� ��׷ο� ������ ��׷ΰ� ���� ��
			if (citizen_1_aggro == madongseok_aggro) { // �ù� ��׷� == ������ ��׷�
				zombie_move_citizen_func();
			}
			else { // ���� ��׷� == ������ ��׷�
				zombie_move_villain_func();
			}
		}
	}
}

// [ PDF 2-4 <�ൿ> & 2-4 <�ൿ> : ����ó�� ]
// 6-7) �������� ���� �ٵ�⿡ ���������� or �������� ���� ���� �̵� ���� �Լ�
int zombie_move_or_not_func() {
	if (zombie_move_or_not == 0) { // ���� �ٵ�⿡ �������� ��
		phase -= 1;
	}
	else { // ���� �ٵ�⿡ �������� ��
		phase = phase;
	}
	return phase;
}


// [ PDF 2-3 < �̵� > & 2-3 < �̵� > :����ó�� ], [ PDF 2-4 <�ൿ> & 2-4 <�ൿ> : ����ó�� ]
// 6-8) ���� -> ������ �̵� �Լ�
int zombie_move_madongseok_func() {
	// �������� ���� �ٵ�⸦ �������� �� (���� �̵� �Ұ�)
	zombie_move_or_not_func();
	// �������� �̹� ������ ���� ��
	if (zombie + 1 == madongseok) {
		zombie = zombie;
	}
	else { // ������ ���� ���� ��
		pre_zombie = zombie;
		zombie -= 1;
	}
}

// [ PDF 2-3 < �̵� > & 2-3 < �̵� > :����ó�� ], [ PDF 2-4 <�ൿ> & 2-4 <�ൿ> : ����ó�� ]
// 6-9) ���� -> �ù� �̵� �Լ�
int zombie_move_citizen_func() {
	// �������� ���� �ٵ�⸦ �������� �� (���� �̵� �Ұ�)
	zombie_move_or_not_func();
	// �ùΰ� �̹� ������ ���� ��
	if (zombie - 1 == citizen_1) {
		zombie = zombie;
	}
	else { // ������ ���� ���� ��
		pre_zombie = zombie;
		zombie -= 1;
	}
}

// [ PDF 2-2 ~ 2-4�� ���̴� �Լ��� ���� ]
// 7) ������ �ൿ �Լ� ���� 
int madongseok_action_func(); // ������ �ൿ ���� �Լ�
int madongseok_action_0_func(); // ������ �ൿ�� 0�� �Է� �޾��� ���� �Լ�
int madongseok_action_1_func(); // ������ �ൿ�� 1�� �Է� �޾��� ���� �Լ�
int madongseok_action_2_func(); // ������ �ൿ�� 2�� �Է� �޾��� ���� �Լ�
int madongseok_action_withzombie_func(); // �������� ����� ������ ����� �Լ�
int madongseok_aggro_max_func(); // ������ ��׷ΰ� �ִ븦 ���� �ʱ� ���� �Լ�
int madongseok_action_start_func(); // ������ �ൿ �Է� �޾��� �� �����ų �Լ�
int madongseok_move_0_func(); // ������ �̵��� 0�� �Է� �޾��� ���� �Լ�
int madongseok_move_1_func(); // ������ �̵��� 1�� �Է� �޾��� ���� �Լ�

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-1) ������ (action) �޽� �Լ� (0�� �Է� �޾��� ��)
int madongseok_action_0_func() {
	printf("madongseok rests...\n");
	pre_madongseok_aggro = madongseok_aggro;
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_aggro -= 1;
	madongseok_stamina += 1;
	if (madongseok_aggro <= AGGRO_MIN) { // ������ ��׷ΰ� ARRGO_MIN���� �۾��� ��
		madongseok_aggro = AGGRO_MIN;
	}
	else {

	}
	if (madongseok_stamina >= STM_MAX) { // ������ ü���� STM_MAX ���� Ŀ�� ��
		madongseok_stamina = STM_MAX;
	}
	else {

	}
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-2) ������ (move) �޽� �Լ� (0�� �Է¹޾��� ��)
int madongseok_move_0_func() {
	madongseok_aggro -= 1;
	if (madongseok_aggro <= AGGRO_MIN) {
		madongseok_aggro = AGGRO_MIN;
	}
	else {

	}
	printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", madongseok, madongseok_aggro, madongseok_stamina);
}

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-3) ������ (move) �������� �̵� ���� �� �Լ� (1�� �Է����� ��) 
int madongseok_move_1_func() {
	madongseok_aggro += 1;
	if (madongseok_aggro >= AGGRO_MAX) {
		madongseok_aggro = AGGRO_MAX;
	}
	else {

	}
}

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-4) ������ �ִ� ��׷� �� ���׹̳� (2�� �Է� �ൿ�κ� ����ó��) �Լ� ����
int madongseok_aggro_max_func() {
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro += 2;
	pre_madongseok_stamina = madongseok_stamina;
	madongseok_stamina -= 1;
	// ������ ü���� 0 �Ʒ��� �������� ��
	if (madongseok_stamina < STM_MIN) {
		madongseok_stamina = STM_MIN;
	}
	// ������ ��׷ΰ� �ִ� ��׷ΰ� �Ǿ��� ��
	if (madongseok_aggro >= AGGRO_MAX) {
		madongseok_aggro = 5;
	}
	else {
		madongseok_aggro += 1;
	}
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, pre_madongseok_stamina, madongseok_stamina);
}

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó��
// 7-5) ������ ���� �Լ� (1�� �Է� �޾��� ��) ]
int madongseok_action_1_func() {
	printf("madongseok provoked zomebie...\n");
	pre_madongseok_aggro = madongseok_aggro;
	madongseok_aggro = AGGRO_MAX;
	printf("madongseok : %d (aggro: %d -> %d, stamina: %d)\n", madongseok, pre_madongseok_aggro, madongseok_aggro, madongseok_stamina);
}

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-6) ������ �ٵ�� �Լ� (2�� �Է� �޾��� ��)
int madongseok_action_2_func() {
	if (100 - p >= k) {
		zombie_move_or_not = 0; // �������� ���� �ٵ�⿡ �������� �� ���� �� �����̰� �ϱ� ���� ���� 
		printf("madongseok pulled zombie... Next turn, it can't move\n");
		madongseok_aggro_max_func();
		zombie_move_or_not_func();
	}
	else {
		zombie_move_or_not = 1; // �������� ���� �ٵ�⿡ �������� �� ���� �����̰� �ϱ� ���� ����
		printf("madongseok failed to pull zombie\n");
		madongseok_aggro_max_func();
		zombie_move_or_not_func();
	}
}

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-7) ������ �ൿ �Է� �޾��� �� �����ų �Լ�
int madongseok_action_start_func() {
	if (madongseok_action == 0) { // 0�� �Է� �޾��� ��
		madongseok_action_0_func();  // ������ �޽� �Լ� �ҷ�����
	}
	else if (madongseok_action == 1) { // 1�� �Է� �޾��� ��
		madongseok_action_1_func(); // ������ ���� �Լ� �ҷ�����
	}
	else if (madongseok_action == 2) { // 2�� �Է� �޾��� ��
		madongseok_action_2_func(); //������ �ٵ�� �Լ� �ҷ�����
	}
	else {

	}
}

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-8) ������ (����� ������ ���) �ൿ ��Ģ �Լ�
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

// [ PDF 2-4 <�ൿ> & <�ൿ> : ����ó�� ]
// 7-9) ������ �ൿ ���� �Լ� 
int madongseok_action_func() {
	// ��ȿ�� ���� �Էµ� ������ ���� �ݺ�
	while (1) {
		printf("madongseok action(0.rest, 1.provoke)>>");
		scanf_s("%d", &madongseok_action);
		printf("\n");
		if (zombie + 1 != madongseok) {
			if (madongseok_action == MOVE_STAY || madongseok_action == MOVE_LEFT) { // 0 �Ǵ� 1�� �Է����� ��
				if (madongseok_action == MOVE_STAY) { // 0�� �Է����� �� 
					madongseok_action_0_func(); // ������ �޽� �Լ� �ҷ�����
					break;
				}
				else { // 1�� �Է����� ��
					madongseok_action_1_func(); // ������ ���� �Լ� �ҷ�����
					break;
				}
			}
		}
	}
}

// 8) --<<<  �λ���(2) �Լ�  >>>--
int busanhang2_func();

int busanhang2_func() {
	train_length_func(); // ���� ���� ���(����ó�� O) �Լ� �ҷ�����
	madongseok_stamina_func(); // ������ ü�� (����ó�� O) �Լ� �ҷ�����
	probability_func(); // Ȯ�� �Է� (����ó�� O) �Լ� �ҷ�����
	printf("\n");
	train_shape_main_func(); // ���� �ʱ� ���� �ҷ�����
	printf("\n\n\n");
	// -< ���� �ڵ� ���� �κ� >-
	while (1) {
		r = rand() % 101; // �ù� ���� ���
		k = rand() % 101; // ������ ���� ���
		zombie_move_func();
		citizen_move_func();
		printf("\n");
		train_shape_main_func();
		printf("\n");

		// citizen_move_func() ���� ���� �ù��� �������� ��� or �� �������� ���
		if (citizen_1 == pre_citizen_1) { // �ù��� �������� �ʾ��� ��
			if (citizen_1_aggro == AGGRO_MIN) { // �ù� ��׷ΰ� 0�� ��
				printf("citizen: stay %d (aggro: %d -> %d)\n", citizen_1, pre_citizen_1_aggro, citizen_1_aggro);
			}
			else { // �ù� ��׷ΰ� 0�� �ƴ� ��
				printf("citizen: stay %d (aggro: %d -> %d)\n", citizen_1, pre_citizen_1_aggro, citizen_1_aggro);
			}
		}
		else { // �ù��� �������� ��
			printf("citizen: %d -> %d (aggro: %d -> %d)\n", pre_citizen_1, citizen_1, pre_citizen_1_aggro, citizen_1_aggro);
		}

		// zombie_move_func() ���� ���� ���� �������� ��� or �� �������� ���
		if (zombie_move_or_not == 1) { // �������� �ٵ�� �Լ����� �������� ��
			if (zombie == pre_zombie) {
				printf("zombie: stay %d\n", zombie);
			}
			else {
				printf("zombie: %d -> %d\n", pre_zombie, zombie);
			}
		}
		else { // �������� �ٵ�� �Լ����� �������� ��
			printf("zombie: stay %d\n", zombie);
		}

		printf("\n");
		madongseok_move_func(); // ������ �̵� ���� �Լ�
		printf("\n");
		train_shape_main_func(); // ���� ���� ��� �Լ�
		printf("\n\n");

		// ������ �̵�
		if (madongseok_move == 0) { // 0�� �Է¹޾��� ��
			madongseok_move_0_func();
		}
		else { // 1�� �Է� �޾��� ��
			madongseok_move_1_func();
		}

		printf("\n");

		printf("citizen does nothing.\n");
		// �ù��� Ż������ ��
		if (citizen_1 == 1) {
			printf("GAME CLEAR! citizen safe !!");
			break;
		}

		// ���� ���� ����
		if (zombie - 1 == citizen_1 && zombie + 1 == madongseok) { // ���� �ùΰ� ������ �� �� ������ ���� ��
			if (citizen_1_aggro > madongseok_aggro) { // �ù��� ��׷ΰ� �� Ŭ ��
				printf("GAME OVER! citizen dead...");
				break;
			}
			else { // �������� ��׷ΰ� �� Ŭ ��
				madongseok_aggro_biggerthan_citizen_villain_func();
				if (madongseok_stamina == STM_MIN) { // ������ ü���� STM_MIN �� ��
					printf("GAME OVER! madongseok_dead...");
					break;
				}
			}
		}
		else if (zombie - 1 == citizen_1 || zombie + 1 == madongseok) { // ���� �ù� �Ǵ� ������ �� �� �Ѹ��� ���������� ��
			if (zombie - 1 == citizen_1) { // ����� �ù��� ���������� ��
				printf("GAME OVER! citizen dead...");
				break;
			}
			else { // ����� �������� ���������� ��
				if (madongseok_stamina == STM_MIN) { // ������ ü���� STM_MIN �� ��
					printf("GAME OVER! madongseok dead...");
					break;
				}
			}
		}
		else { // �� �� ���������� ���� ��
			printf("zombie attacked nobody.\n");
		}

		// ������ �ൿ ����
		if (madongseok == zombie + 1) { // �������� ����� ������ ��
			madongseok_action_withzombie_func(); // ������ �ൿ �Լ� �ҷ�����
		}
		else { // �������� ����� �������� ���� ��
			madongseok_action_func(); // ������ �ൿ �Լ� �ҷ�����
		}
		//
		phase += 1; // ���� 1 ������Ų��.
	} // <- while �� �߰�ȣ
}



// --<< �λ���(3) [ PDF 3-2 ] �߰��� ���� ���� >>--

// int villain; // ����
// int pre_villain; // ���� (��) ����
// int j; // ���� ���� 
// int villain_aggro; // ���� ��׷�
// int villain_pre_aggro; // ���� (��) ��׷� ����

// --<< �λ���(3) [ PDF 3-2 ] �߰��� �Լ� ���� >>--

// 1) ���� ���� (�Է� �� ����ó��) �Լ� ����
int BSH3_2_train_length_func();
int BSH3_2_train_length_func() {
	// ��ȿ�� ���� �Էµ� ������ ���ѹݺ�
	while (1) {
		printf("train length(%d ~ %d)>>", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
		// ���� ���̰� 15 ~ 50 ������ ��
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			break;
		}
	}
	// * ������, �ù� 1, ����, ���� �ʱ� ��ġ ���� *
	madongseok = train_length - 2;
	zombie = train_length - 3;
	citizen_1 = train_length - 6;
	pre_citizen_1 = citizen_1;
	villain = train_length - 5;
	pre_villain = villain;
	pre_zombie = zombie;
	pre_madongseok = madongseok;
}
// 2) ���� ��� (�ù�, ����, ����, ������ ��ġ) �Լ� ���� 
int BSH3_2_train_shape_main_func();
int BSH3_2_train_shape_first_third_func();
int BSH3_2_train_shape_second_func();

// 2-1) ���� ù° ��, ��° ��
int BSH3_2_train_shape_first_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// 2-2) ���� ��° ��
int BSH3_2_train_shape_second_func() {
	for (int i = 0; i < train_length; i++) {
		// ������ ó���� ���� '#' ���� ������
		if (i == 0 || i == train_length - 1) {
			printf("#");
		}
		else if (i == citizen_1) {
			printf("C");
		}
		else if (i == villain) {
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

// 2-3) ���� �Լ� ����
int BSH3_2_train_shape_main_func() {
	BSH3_2_train_shape_first_third_func();
	BSH3_2_train_shape_second_func();
	BSH3_2_train_shape_first_third_func();
}

// 3) ���� �̵� (�߾� Ȯ�� & ��׷� ����ó��) �Լ� ����
int villain_move_func();
int villain_move_func() {
	if (citizen_1 + 1 != villain) { // ������ �ù�1�� ������ ���� ���� ��
		pre_villain = villain;
		villain = citizen_1 + 1;
		villain_pre_aggro = villain_aggro;
		// ���� ��׷ΰ� AGGRO_MAX �� ��
		if (villain_aggro >= AGGRO_MAX) {
			villain_aggro = 5;
		}
		else { // ���� ��׷ΰ� AGGRO_MAX�� �ƴ� ��
			villain_aggro += 1;
		}
	}
	else { // ������ �ù�1�� ���������� ��
		if (100 - p >= j) { // ������ �߾� �õ��� �������� ��
			pre_citizen_1 = citizen_1; // �ù� 1�� ���� �ڸ��� �̵��ϱ� ��, �̵� �� ������ ����
			citizen_1 = villain; // �ù� 1�� ���� �ڸ��� �̵�
			pre_villain = villain; // ������ �ù� 1 �ڸ��� �̵��ϱ� ��, �̵� �� ������ ����
			villain = pre_citizen_1; // ������ �ù� 1 �ڸ��� �̵�
		}
		else { // ������ �߾� �õ��� �������� ��
			// �ƹ� �ൿ ����
		}
	}
}

// 4) ���� ��׷ο� ������ ��׷ΰ� ���� ���� �Լ� ����
int zombie_move_villain_func();
int zombie_move_villain_func() {
	if (zombie - 1 == villain) { // ���� �����̶� ������ ��
		zombie = zombie;
	}
	else { // ������ ���� ���� ��
		pre_zombie = zombie;
		zombie -= 1;
	}
}

// 9) --<<<   �λ���(3) [ PDF 3-2. ��������2: ���� ]  >>>--
int busanhang3_2_func();
int busanhang3_2_func() {
	printf("�λ��� 3_2\n");
	BSH3_2_train_length_func(); // ���� ���� ���(����ó�� O) �Լ� �ҷ�����
	madongseok_stamina_func(); // ������ ü�� (����ó�� O) �Լ� �ҷ�����
	probability_func(); // Ȯ�� �Է� (����ó�� O) �Լ� �ҷ�����
	printf("\n");
	BSH3_2_train_shape_main_func(); // ���� �ʱ� ���� �ҷ�����
	printf("\n\n\n");
	// -< ���� �ڵ� ���� �κ� >-
	while (1) {
		r = rand() % 101; // �ù� ���� ���
		k = rand() % 101; // ������ ���� ���
		j = 30; // ���� �߾� �õ� Ȯ��
		citizen_move_func(); // �ù� �̵� �Լ� �ҷ�����
		villain_move_func(); // ���� �̵� �Լ� �ҷ�����
		zombie_move_func(); // ���� �̵� �Լ� �ҷ�����
		printf("\n");
		BSH3_2_train_shape_main_func(); // ���� ���� �ҷ�����
		printf("\n");

		// citizen_move_func() ���� ���� �ù��� �������� ��� or �� �������� ���
		if (citizen_1 == pre_citizen_1) { // �ù��� �������� �ʾ��� ��
			if (citizen_1_aggro == AGGRO_MIN) { // �ù� ��׷ΰ� 0�� ��
				printf("citizen: stay %d (aggro: %d -> %d)\n", citizen_1, pre_citizen_1_aggro, citizen_1_aggro);
			}
			else { // �ù� ��׷ΰ� 0�� �ƴ� ��
				printf("citizen: stay %d (aggro: %d -> %d)\n", citizen_1, pre_citizen_1_aggro, citizen_1_aggro);
			}
		}
		else { // �ù��� �������� ��
			printf("citizen: %d -> %d (aggro: %d -> %d)\n", pre_citizen_1, citizen_1, pre_citizen_1_aggro, citizen_1_aggro);
		}

		// villain_move_func() ���� ���� ������ �������� ��� or �� �������� ���
		if (villain == pre_villain) { // ������ �������� �ʾ��� ��
			if (villain_aggro == AGGRO_MIN) { // ���� ��׷ΰ� 0�� ��
				printf("villain: stay %d (aggro: %d -> %d)\n", villain, villain_pre_aggro, villain_aggro);
			}
			else { // ���� ��׷ΰ� 0�� �ƴ� ��
				printf("villain: stay %d (aggro: %d -> %d)\n", pre_villain, villain_pre_aggro, villain_aggro);
			}
		}
		else { // ������ �������� ��
			printf("villain: %d -> %d (aggro: %d -> %d)\n", pre_villain, villain, villain_pre_aggro, villain_aggro);
		}


		// zombie_move_func() ���� ���� ��
		// �� �������� ��� or �� �������� ���
		if (zombie_move_or_not == 1) { // �������� �ٵ�� �Լ����� �������� ��
			if (zombie == pre_zombie) { // ���� ������ ���� ��
				printf("zombie: stay %d\n", zombie);
			}
			else { // ���� �������� ��
				printf("zombie: %d -> %d\n", pre_zombie, zombie);
			}
		}
		else { // �������� �ٵ�� �Լ����� �������� ��
			printf("zombie: stay %d\n", zombie);
		}

		printf("\n");
		madongseok_move_func(); // ������ �̵� ���� �Լ�
		printf("\n");
		BSH3_2_train_shape_main_func(); // ���� ���� ��� �Լ�
		printf("\n\n");

		// ������ �̵�
		if (madongseok_move == 0) { // 0�� �Է¹޾��� ��
			madongseok_move_0_func();
		}
		else { // 1�� �Է� �޾��� ��
			madongseok_move_1_func();
		}

		printf("\n");

		printf("citizen does nothing.\n");
		// �ù��� Ż������ ��
		if (citizen_1 == 1) {
			printf("GAME CLEAR! citizen safe !!");
			break;
		}

		// ���� ���� ����
		if (zombie - 1 == citizen_1 && zombie + 1 == madongseok || zombie - 1 == villain && zombie + 1 == madongseok) { // ���� �ùΰ� ������ �� �� ������ ���� ��
			if (citizen_1_aggro > madongseok_aggro) { // �ù��� ��׷ΰ� �� Ŭ ��
				printf("GAME OVER! citizen dead...");
				break;
			}
			else if (madongseok_aggro > citizen_1 || madongseok_aggro > villain_aggro) { // �������� ��׷ΰ� �� Ŭ ��
				madongseok_aggro_biggerthan_citizen_villain_func();
				if (madongseok_stamina == STM_MIN) { // ������ ü���� STM_MIN �� ��
					printf("GAME OVER! madongseok_dead...");
					break;
				}
			}
			else { // ������ ��׷ΰ� �� Ŭ ��
				villain = -1;
				printf("villain dead...\n");
			}
		}
		else if (zombie - 1 == citizen_1 || zombie + 1 == madongseok || zombie - 1 == villain) { // ���� �ù� �Ǵ� ������ �Ǵ� ���� �� �� �Ѹ��� ���������� ��
			if (zombie - 1 == citizen_1) { // ����� �ù��� ���������� ��
				printf("GAME OVER! citizen dead...");
				break;
			}
			else if (zombie + 1 == madongseok) { // ����� �������� ���������� ��
				if (madongseok_stamina == STM_MIN) { // ������ ü���� STM_MIN �� ��
					printf("GAME OVER! madongseok dead...");
					break;
				}
			}
			else if (villain == zombie - 1) { //  ����� ������ ���������� ��
				villain = -1;
				printf("villain dead...\n");
			}
			else {

			}
		}
		else { // �� �� ���������� ���� ��
			printf("zombie attacked nobody.\n");
		}

		// ������ �ൿ ����
		if (madongseok == zombie + 1) { // �������� ����� ������ ��
			madongseok_action_withzombie_func(); // ������ �ൿ �Լ� �ҷ�����
		}
		else { // �������� ����� �������� ���� ��
			madongseok_action_func(); // ������ �ൿ �Լ� �ҷ�����
		}
		//
		phase += 1; // ���� 1 ������Ų��.
	} // <- while �� �߰�ȣ
}




// --<< �λ���(3) [ PDF 3-3 ] �߰��� ���� ���� >>--

int citizen_2; // �ù� 2
int pre_citizen_2; // �ù� 2 (��) ����
int citizen_3; // �ù� 3
int pre_citizen_3; // �ù� 3 (��) ����
int citizen_2_aggro; // �ù� 2 ��׷�
int pre_citizen_2_aggro; // �ù� 2 (��) ��׷�
int citizen_3_aggro; // �ù� 3 ��׷�
int pre_citizen_3_aggro; // �ù� 3 (��) ��׷�


// --<< �λ���(3) [ PDF 3-3 ] �߰��� �Լ� ���� >>--


































































// --<< ���� �ڵ� �ۼ� >>--
int main(void) {
	// -< ���� �ڵ� �ʱ� �κ� >-
	srand((unsigned int)time(NULL)); // ������ ���� ����
	// -< ���� �ڵ� ���� �κ� >-
	// busanhang2_func(); // �λ���(2) �Լ� �ҷ����� ! !
	busanhang3_2_func(); // �λ���(3-2) �Լ� �ҷ����� ! !
	return 0;
} // <- int main(void) �߰�ȣ
