#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int** creat_matrix(int row, int col); //���� �޸��Ҵ� ������� ��� ����
int free_matrix(int** matrix, int row, int col); //���� ���� �� �޸� ����
void print_matrix(int** matrix, int row, int col); //��� ���
int fill_data(int** matrix, int row, int col); //0~19 ������ ���������� ��� �Է�
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col); //����� ����
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col); //����� ����
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //��ġ���
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col); //����� ����

int main() {

	int** matrix_a;
	int** matrix_b;
	int** matrix_sum;
	int** matrix_sub;
	int** matrix_axt;
	int** matrix_t;

	int row, col;

	srand(time(NULL)); // rand()��� �Լ��� �������� �õ尪�� �ֱ����� �Լ�, NULL���� �ʱ�ȭ
	printf("��� �� �Է��ϼ��� : ");
	scanf("%d %d", &row, &col);
	
	if (row <= 0 || col <= 0) {
		printf("���������� �Է��Դϴ�.");
		return 0;
	} // row�� col�� 0�����̸� �������� �Է����� ���α׷��� �����Ѵ�.

		
	//���� �޸��Ҵ�
	matrix_a = creat_matrix(row, col); //creat_matrix �Լ� ȣ���Ͽ� matrix_a�� �����Ѵ�.
	matrix_b = creat_matrix(row, col); ////creat_matrix �Լ� ȣ���Ͽ� matrix_b�� �����Ѵ�.
	
	//���� �Է¹ޱ�
	fill_data(matrix_a, row, col); // fill_data �Լ��� matrix_a, row, col�� ���ڷ� �Ѱ��ش�.
	fill_data(matrix_b, row, col);// fill_data �Լ��� matrix_b, row, col�� ���ڷ� �Ѱ��ش�.

	//�����޸��Ҵ�
	matrix_sum = creat_matrix(row, col); //creat_matrix �Լ� ȣ���Ͽ� matrix_sum�� �����Ѵ�.
	matrix_sub = creat_matrix(row, col);//creat_matrix �Լ� ȣ���Ͽ� matrixsub�� �����Ѵ�.
	matrix_axt = creat_matrix(row, col);//creat_matrix �Լ� ȣ���Ͽ� matrix_axt�� �����Ѵ�.

  
	if (row == col) {
		matrix_t = creat_matrix(row, col);
	}
	else {  //row�� col�� �ٸ��� ��� �� �ٲ㼭 ���� ����
		matrix_t = creat_matrix(col, row);
	}

	//������
	printf("��� A : ");
	printf("\n");
	print_matrix(matrix_a, row, col);

	printf("��� B : ");
	printf("\n");
	print_matrix(matrix_b, row, col);

	printf("��� ���� (A + B) :");
	printf("\n");
	addition_matrix(matrix_a, matrix_b, matrix_sum, row, col);
	print_matrix(matrix_sum, row, col);

	printf("��� ���� (A - B) :");
	printf("\n");
	subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);
	print_matrix(matrix_sub, row, col);

	printf("A�� ��ġ ��� T:");
	printf("\n");
	transpose_matrix(matrix_a, matrix_t, row, col);
	print_matrix(matrix_t, col, row);

	printf("��� ���� (A X T) :");
	printf("\n");
	if (row != col) { //row�� col�� �ٸ���  ���� �Ұ���
		printf("������ �Ұ��� �մϴ�.\n");
		printf("\n");
		return 1;
	}
	else { //row�� col�� ������ ���� ����
		multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);
		print_matrix(matrix_axt, row, col);
	}

	//��ĵ����Ҵ�����
	free_matrix(matrix_a, row, col);
	free_matrix(matrix_b, row, col);
	free_matrix(matrix_sum, row, col);
	free_matrix(matrix_sub, row, col);
	free_matrix(matrix_axt, row, col);

	return 0;
}

int** creat_matrix(int row, int col) {

	int** matrix;

	matrix = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; ++i) {
		matrix[i] = (int*)malloc(col * sizeof(int)); // �ݺ����� ����  matrix[i]�� �޸𸮸� �Ҵ�޴´�.
		for (int j = 0; j < col; ++j) {
			matrix[i][j] = 0; //matrix[i][j]�� ���� 0���� �ʱ�ȭ ���ش�.
		}
	}
	if (matrix == NULL) {
		printf("���������� ����Դϴ�.");
	}
	return matrix; //matrix�� ��ȯ���ش�.
}

int fill_data(int** matrix, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 20; //matrix[i][j]�� 0~19������ ���� �������� �־��ش�.
		}
	}
	return **matrix; //**matrix�� ��ȯ���ش�.
} 


int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col) {
	if (row <= 0 || col <= 0) {
		printf("���������� �Է��Դϴ�.");
		return NULL;
	}
	//row�� col�� 0�����̸� �����޼��� ���

	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //���A�� B�� ���� matrix_sum�� ����
	}
	if (matrix_sum == NULL) {
		printf("���������� ����Դϴ�.");
	}
	return 0;

} 

int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub,
	int row, int col) {
	if (row <= 0 || col <= 0) {
		printf("���������� �Է��Դϴ�.");
		return NULL;
	}
	//row�� col�� 0�����̸� �����޼��� ���

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; //���A���� B�� �� matrix_sub�� ����
	}
	if (matrix_sub == NULL) {
		printf("���������� ����Դϴ�.");
	}
	return 0;

} 
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {

	if (row <= 0 || col <= 0) {
		printf("���������� �Է��Դϴ�.");
		return NULL;
	}  //row�� col�� 0�����̸� �����޼��� ���

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_t[j][i] = matrix[i][j]; //���ڷ� ���� ���� matrix�� i�� j�� �ٲ� matrix_t�� ����
		}
	}
	if (matrix_t == NULL) {
		printf("���������� ����Դϴ�.");
	}
	return 0;
} 

int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col) {

	if (row <= 0 || col <= 0) {
		printf("���������� �Է��Դϴ�.");
		return NULL;
	} //row�� col�� 0�����̸� �����޼��� ���
	
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			matrix_axt[i][j] = 0; // ����� ������ �ϱ� ���� matrix_axt[i][j] 0���� �ʱ�ȭ
		}
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			for (int k = 0; k < row; k++){ 
				matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j]; //��� A�� T�� ���� matrix_axt�� ����
			}
		}
	}

	if (matrix_axt == NULL) {
		printf("���������� ����Դϴ�.");
	}
	return 0;
} 

void print_matrix(int** matrix, int row, int col) { 

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			printf("%3d ", matrix[i][j]); // �ڸ����� ���� ��� ���
		printf("\n");
	}
	printf("\n");

} 

int free_matrix(int** matrix, int row, int col) {  //�޸�����

	for (int i = 0; i < row; ++i)
		free(matrix[i]); 
        
	return 0;
} 
