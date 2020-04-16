#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int** creat_matrix(int row, int col); //동적 메모리할당 방식으로 행렬 생성
int free_matrix(int** matrix, int row, int col); //연산 종료 후 메모리 해제
void print_matrix(int** matrix, int row, int col); //행렬 출력
int fill_data(int** matrix, int row, int col); //0~19 사이의 랜덤값으로 행렬 입력
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col); //행렬의 덧셈
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col); //행렬의 뺄셈
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //전치행렬
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col); //행렬의 곱셈

int main() {

	int** matrix_a;
	int** matrix_b;
	int** matrix_sum;
	int** matrix_sub;
	int** matrix_axt;
	int** matrix_t;

	int row, col;

	srand(time(NULL)); // rand()라는 함수에 무작위의 시드값을 주기위한 함수, NULL으로 초기화
	printf("행과 열 입력하세요 : ");
	scanf("%d %d", &row, &col);
	
	if (row <= 0 || col <= 0) {
		printf("비정상적인 입력입니다.");
		return 0;
	} // row나 col이 0이하이면 비정상적 입력으로 프로그램을 종료한다.

		
	//동적 메모리할당
	matrix_a = creat_matrix(row, col); //creat_matrix 함수 호출하여 matrix_a에 저장한다.
	matrix_b = creat_matrix(row, col); ////creat_matrix 함수 호출하여 matrix_b에 저장한다.
	
	//성분 입력받기
	fill_data(matrix_a, row, col); // fill_data 함수에 matrix_a, row, col을 인자로 넘겨준다.
	fill_data(matrix_b, row, col);// fill_data 함수에 matrix_b, row, col을 인자로 넘겨준다.

	//동적메모리할당
	matrix_sum = creat_matrix(row, col); //creat_matrix 함수 호출하여 matrix_sum에 저장한다.
	matrix_sub = creat_matrix(row, col);//creat_matrix 함수 호출하여 matrixsub에 저장한다.
	matrix_axt = creat_matrix(row, col);//creat_matrix 함수 호출하여 matrix_axt에 저장한다.

  
	if (row == col) {
		matrix_t = creat_matrix(row, col);
	}
	else {  //row와 col이 다르면 행과 열 바꿔서 인자 전달
		matrix_t = creat_matrix(col, row);
	}

	//행렬출력
	printf("행렬 A : ");
	printf("\n");
	print_matrix(matrix_a, row, col);

	printf("행렬 B : ");
	printf("\n");
	print_matrix(matrix_b, row, col);

	printf("행렬 덧셈 (A + B) :");
	printf("\n");
	addition_matrix(matrix_a, matrix_b, matrix_sum, row, col);
	print_matrix(matrix_sum, row, col);

	printf("행렬 뺄셈 (A - B) :");
	printf("\n");
	subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);
	print_matrix(matrix_sub, row, col);

	printf("A의 전치 행렬 T:");
	printf("\n");
	transpose_matrix(matrix_a, matrix_t, row, col);
	print_matrix(matrix_t, col, row);

	printf("행렬 곱셈 (A X T) :");
	printf("\n");
	if (row != col) { //row와 col이 다르면  곱셈 불가능
		printf("곱셈이 불가능 합니다.\n");
		printf("\n");
		return 1;
	}
	else { //row와 col이 같으면 곱셈 가능
		multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);
		print_matrix(matrix_axt, row, col);
	}

	//행렬동적할당해제
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
		matrix[i] = (int*)malloc(col * sizeof(int)); // 반복문을 통해  matrix[i]에 메모리를 할당받는다.
		for (int j = 0; j < col; ++j) {
			matrix[i][j] = 0; //matrix[i][j]의 값을 0으로 초기화 해준다.
		}
	}
	if (matrix == NULL) {
		printf("비정상적인 결과입니다.");
	}
	return matrix; //matrix를 반환해준다.
}

int fill_data(int** matrix, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 20; //matrix[i][j]에 0~19까지의 수를 랜덤으로 넣어준다.
		}
	}
	return **matrix; //**matrix를 반환해준다.
} 


int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col) {
	if (row <= 0 || col <= 0) {
		printf("비정상적인 입력입니다.");
		return NULL;
	}
	//row나 col이 0이하이면 에러메세지 출력

	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //행렬A와 B를 더해 matrix_sum에 저장
	}
	if (matrix_sum == NULL) {
		printf("비정상적인 결과입니다.");
	}
	return 0;

} 

int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub,
	int row, int col) {
	if (row <= 0 || col <= 0) {
		printf("비정상적인 입력입니다.");
		return NULL;
	}
	//row나 col이 0이하이면 에러메세지 출력

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; //행렬A에서 B를 빼 matrix_sub에 저장
	}
	if (matrix_sub == NULL) {
		printf("비정상적인 결과입니다.");
	}
	return 0;

} 
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {

	if (row <= 0 || col <= 0) {
		printf("비정상적인 입력입니다.");
		return NULL;
	}  //row나 col이 0이하이면 에러메세지 출력

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_t[j][i] = matrix[i][j]; //인자로 전달 받은 matrix를 i와 j를 바꿔 matrix_t에 저장
		}
	}
	if (matrix_t == NULL) {
		printf("비정상적인 결과입니다.");
	}
	return 0;
} 

int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col) {

	if (row <= 0 || col <= 0) {
		printf("비정상적인 입력입니다.");
		return NULL;
	} //row나 col이 0이하이면 에러메세지 출력
	
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			matrix_axt[i][j] = 0; // 행렬의 곱셈을 하기 위해 matrix_axt[i][j] 0으로 초기화
		}
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			for (int k = 0; k < row; k++){ 
				matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j]; //행렬 A와 T를 곱해 matrix_axt에 저장
			}
		}
	}

	if (matrix_axt == NULL) {
		printf("비정상적인 결과입니다.");
	}
	return 0;
} 

void print_matrix(int** matrix, int row, int col) { 

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			printf("%3d ", matrix[i][j]); // 자릿수에 맞춰 행렬 출력
		printf("\n");
	}
	printf("\n");

} 

int free_matrix(int** matrix, int row, int col) {  //메모리해제

	for (int i = 0; i < row; ++i)
		free(matrix[i]); 
        
	return 0;
} 
