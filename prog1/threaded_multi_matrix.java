/* Name:        Benjamin Guitreau           */
/* Project:     PA-1a(MultiThreading)       */
/* File:        threaded_multi_matrix.java  */
/* Instructor:  Feng Chen                   */
/* Class:       cs4103-au14                 */
/* LogonID:     cs410312                    */

public class threaded_multi_matrix {

    public static void main(String[] args) {
        int A_row;
        int A_col;
        int B_row;
        int B_col;
        A_row = B_col = 3;
        B_row = A_col = 2;

        // AB = C
        int [][]A = {{1, 4}, {2, 5}, {3, 6}};
        int [][]B = {{8, 7, 6}, {5, 4, 3}};
        int [][]C = new int [A_row][B_col];

        final int NUM_THREADS = 9;
        Thread[] workers = new Thread[NUM_THREADS];

        try {
            for (int i = 0 ; i < A_row; i++) {
                for (int j = 0; j < B_col; j++) {
                    workers[i * 3 + j] = new Thread(new worker_thread(i, j, A, B, C));
                    workers[i * 3 + j].start();
                    workers[i * 3 + j].join();
                }
            }

        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("AB=C");
        print_matrix(A_row, A_col, A, "A");
        System.out.print("\n");
        print_matrix(B_row, B_col, B, "B");
        System.out.print("\n");
        print_matrix(A_row, B_col, C, "C");
    }

    public static void print_matrix(int r, int c, int [][]m, String string) {
        System.out.println("Matrix " + string + ":");
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                System.out.print(m[i][j] + " ");
            }
            System.out.print("\n");
        }
    }
}
