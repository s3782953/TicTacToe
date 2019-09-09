import java.util.Scanner;

public class TicTacToe {
    private static int row = 3; // The Row Length
    private static int column = 3; // The Column Height
    private static int[][] plane = new int[row][column]; // The main array
    private static int[][] marker = new int[row][column]; // The copy array
    private static boolean finish = true; // Checks if all the spaces are filled
    private static boolean flick = false; // Flicks true once the computer made a move

    public static void main(String[] args) { // The main method
        while (finish) { // Runs until the finish variable is flase
            player(); // The players move
            complete(); // Checks if all spaces are filled
            algorithm(); // The computers move
            Check();
            status(); // Prints out the status of the game
        }
    }

    private static void player() { // The players method which ask you simple 'Which location do you like to make
                                   // your move?''
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter your move...");
        System.out.println("Enter Width:");
        int user_row = scan.nextInt();
        System.out.println("Enter Length");
        int user_col = scan.nextInt();
        plane[user_row - 1][user_col - 1] = 1;
    }

    private static void algorithm() { //The computers algorithm
        while (flick == false && finish == true) {
            int newrow = 0;
            int newcol = 0;
            double random = Math.round(Math.random() * 8); //Chooses a number bewtween 0-8 (since arrays starts at 0)
            System.out.println(random);
            for (int i = 0; i < random; i++) {
                newcol++;
                if (newcol > 2) {
                    newrow++;
                    newcol = 0;
                }
            }
            if (plane[newrow][newcol] != 2 && plane[newrow][newcol] != 1 && flick == false) {
                plane[newrow][newcol] = 2;
                flick = true;
            }
        }
        flick = false;
    }

    private static void Check() { //Checks if there are any nearby wins

    }

    private static void complete() { // Checks if the game is finish once all spaces are filled out
        int counter = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (plane[i][j] == 0) {
                    counter++;
                }
            }
        }
        if (counter == 0) {
            finish = false;
        }
    }

    private static void status() { // Prints out the status of the game
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                System.out.print("Row " + (i + 1) + ":  Column " + (j + 1) + " : ");
                System.out.println(plane[i][j]);
            }
        }
    }
}
