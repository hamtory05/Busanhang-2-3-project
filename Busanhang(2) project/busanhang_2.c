#include <stdio.h> 
#include <stdlib.h> 
  
// --<< ���� ���� >>--  
  
// 1) �Ķ���� 
#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define STM_MIN 0 // ������ ü��
#define STM_MAX 5 
#define PROB_MIN 10 // Ȯ�� 
#define PROB_MAX 90 
#define AGGRO_MIN 0 // ��׷� ���� 
#define AGGRO_MAX 5
 
// 2) ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 3) ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 4) ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// 5) ���� ����
int train_length; // ���� ����
int madongseok_stamina; //������ ü�� 
int probability, p; // Ȯ��
int citizen; // �ù�
int zombie; // ����
int madongseok; // ������
int aggro = 1; // ��׷�

// --<< �ʿ��� �Լ� ���� >>--

// 1) ���� ���� (�Է� �� ����ó��) �Լ� ����
int train_length_func();
int train_length_func() {
	// ��ȿ�� ���� �Էµ� ������ ���ѹݺ�
	while (1) {
		printf("train length(%d ~ %d)>>", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
		// ���� ���̰� 15 ~ 50 ������ ��
		if (train_length >= LEN_MIN && train_length <= LEN_MAX) {
			// * ������, �ù�, ���� �ʱ� ��ġ ���� *
			int madongseok = train_length - 2, zombie = train_length - 3, citizen = train_length - 6;
			break;
		}
	}
}

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
			break;
		}
	}
}

// 4) ���� ���� (ù°, ��°, ��° ��) �Լ� ����
int train_shape_first_func();
int train_shape_second_func();
int train_shape_third_func();

// ���� ù° ��
int train_shape_first_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// ���� ��° ��
int train_shape_second_func() {
	for (int i = 0; i < train_length; i++) {
		// ������ ó���� ���� '#' ���� ������
		if (i == 0 || i == train_length - 1) {
			printf("#");
		}
		else {}
		if (i == citizen) {
			printf("C");
		}
		else {}
		if (i == zombie) {
			printf("Z");
		}
		else {}
		if (i == madongseok) {
			printf("M");
		}
	}
	printf("\n");
}

// ���� ��° ��
int train_shape_third_func() {
	for (int i = 0; i < train_length; i++) {
		printf("#");
	}
	printf("\n");
}

// --<< ���� �ڵ� �ۼ� >>--
int main(void) {
	train_length_func(); // ���� �Լ� �ҷ�����
	madongseok_stamina_func(); // ������ ü�� �Լ� �ҷ�����
	probability_func(); // Ȯ�� �Լ� �ҷ�����
	train_shape_first_func(); // ���� (ù° ��) ���� �ҷ�����
	train_shape_second_func(); // ���� (��° ��) ���� �ҷ�����
	train_shape_third_func(); // ���� (��° ��) ���� �ҷ�����


} 
