import java.util.Scanner;

public class TicTacToe {
    private static int row = 3; //The Row Length
    private static int column = 3; //The Column Height
    private static int[][] plane = new int[row][column]; //The main array
    private static int[][] marker = new int[row][column]; //The copy array 
    private static boolean finish = true; //Checks if all the spaces are filled
    private static boolean flick = false; //Flicks true once the computer made a move

    public static void main(String[] args) { //The main method
        while (finish) { //Runs until the finish variable is flase
            player(); //The players move
            algorithm(); //The computers move
            status(); //Prints out the status of the game
            complete(); //Checks if all spaces are filled
        } 
    }

    private static void player() { //The players method which ask you simple 'Which location do you like to make your move?''
        Scanner scan = new Scanner(System.in);
            System.out.println("Please enter your move...");
            System.out.println("Enter Width:");
            int user_row = scan.nextInt();
            System.out.println("Enter Length");
            int user_col = scan.nextInt();
            plane[user_row-1][user_col-1] = 1;
    }

    private static void status() { //Prints out the status of the game
        for (int i = 0; i < row; i++)           {
            for (int j = 0; j < column; j++) {
                System.out.print("Row " + (i+1) + ":  Column " + (j+1) + " : ");
                System.out.println(plane[i][j]);
            }
        }
    }

    private static void algorithm() { //The computers algorithm
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                revertmark(i,j);
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

    private static void revertmark(int i, int j) { //Reverts the mark back to 0
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

    private static void set(int i, int j) { //Sets the computers move
        plane[i][j] = 2;
        flick = true;
    }

    private static void place(double random, int i, int j) { //Makes the move at current location else places a marker
        if (random % 2 != 0) {
            plane[i][j] = 2;
            flick = true;
        }
        else {
            marker[i][j] = 3; //If it does not make a move set a marker at the current location
        }
    }

    private static void complete() { //Checks if the game is finish once all spaces are filled out
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (plane[i][j] != 0) {
                    finish = true;
                } else {
                    finish = false;
                }
            }
        }
    }

}
