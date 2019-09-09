import java.util.Scanner;

public class TicTacToe {
    private static int row = 3;
    private static int column = 3;
    private static int[][] plane = new int[row][column];
    private static int[][] marker = new int[row][column];
    private static boolean finish = false;
    private static boolean flick = false;

    public static void main(String[] args) {
        complete();
        while (finish) {
            Scanner scan = new Scanner(System.in);
            System.out.println("Please enter your move...");
            System.out.println("Enter Width:");
            int user_row = scan.nextInt();
            System.out.println("Enter Length");
            int user_col = scan.nextInt();
            plane[user_row][user_col] = 1;
            algorithm();
            status();
        } 
    }   

    private static void status() {
        for (int i = 0; i < row; i++)           {
            for (int j = 0; j < column; j++) {
                System.out.print("Row [" + i + "]:  Column " + j + " : ");
                System.out.println(plane[i][j]);
            }
        }
    }

    private static void algorithm() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                mark(i,j);
                if (plane[i][j] != 1 && flick == false && plane[i][j] != 2) {
                    double random = Math.round(Math.random());
                    place(random, i, j);
                }
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (marker[i][j] == 3 && flick == false) {
                    set(i, j);
                }
            }
        }

        flick = false;
    }

    private static void mark(int i, int j) {
        int tempj = j;
        int tempi = i;
        if (j != 0) {
            tempj--;
        }
        else {
            if (i != 0) {
                tempi--;
            }
        }
        marker[tempi][tempj]=0;
    }

    private static void set(int i, int j) {
        plane[i][j] = 2;
        flick = true;
    }

    private static void place(double random, int i, int j) {
        if (random % 2 != 0) {
            plane[i][j] = 2;
            flick = true;
        }
        else {
            marker[i][j] = 3;
        }
    }

    private static void complete() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (plane[i][j] != 0) {
                    finish = false;
                } else {
                    finish = true;
                }
            }
        }
    }

}
