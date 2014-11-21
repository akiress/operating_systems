/* Name:        Benjamin Guitreau           */
/* Project:     PA-1a(MultiThreading)       */
/* File:        worker_thread.java          */
/* Instructor:  Feng Chen                   */
/* Class:       cs4103-au14                 */
/* LogonID:     cs410312                    */
public class worker_thread extends Thread{
    private int row;
    private int col;
    private int [][] A;
    private int [][] B;
    private int [][] C;

    public worker_thread(int row, int col, int[][] A,
            int[][] B, int[][] C) {
        this.row = row;
        this.col = col;
        this.A = A;
        this.B = B;
        this.C = C;
    }

    public void run() {
        for (int i = 0; i < B.length; i++) {
            C[row][col] += A[row][i] * B[i][col];
        }
    }   
}
