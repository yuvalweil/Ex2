#ifndef HARD_CODED_DATA_FOR_THREAD
#define HARD_CODED_DATA_FOR_THREAD

typedef struct {
	int real_grade;
	int humen_grade;
	int eng_grade;
	int eval_grade;
	int student_avg;
} Student;

enum typeGrade
{
	Real = 1,
	Human = 2,
	Eng = 3,
	Eval = 4,
};

typedef struct
{
	int school_num;
	int real_weight;
	int human_weight;
	int english_weight;
	int eval_weight;
	int number_of_schools;
} MATH_THREAD_params_t;
#endif