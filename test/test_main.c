#include "test_main.h"

int main(void) {
	run_vec3_tests();
	run_col3_tests();
	run_canvas_tests();
	run_mat_tests();
	printf("\nAll tests run successfully.\n");
	return 0;
}
