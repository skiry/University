import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.*;

public class Main {
    static int MAX_WIDTH = 100;
    static int MAX_HEIGHT = 100;
    static int NUMBER_OF_THREADS = 18;
    static boolean PRODUCT = false;

    static int n1, m1;
    static int[][] matrix1 = new int[MAX_HEIGHT][MAX_WIDTH];
    static int n2, m2;
    static int[][] matrix2 = new int[MAX_HEIGHT][MAX_WIDTH];
    static int[][] matrix1copy = new int[MAX_HEIGHT][MAX_WIDTH];
    static int[][] productResult = new int[MAX_HEIGHT][MAX_WIDTH];
    static int numberOfThreads = NUMBER_OF_THREADS;
    static List<Future<Boolean>> futures = new ArrayList<>(100);



    public static class Sum implements Callable<Boolean> {
        int threadNumber;

        // standard constructors
        Sum(int threadNumber){
            this.threadNumber = threadNumber;
        }
        public Boolean call() {
            int from = threadNumber * ((int)(n1 * m1) / numberOfThreads);
            int to = from + ((int)(n1 * m1) / numberOfThreads) - 1;
            int line, column;
            for (int j = from; j <= to; ++j) {
                line = (int)j / m1;
                column = j % m1;
                matrix1[line][column] += matrix2[line][column];
            }

            return true;
        }
    }

    public static class Product implements Callable<Boolean> {
        int threadNumber;

        // standard constructors
        Product(int threadNumber){
            this.threadNumber = threadNumber;
        }
        public Boolean call() {
            int from = threadNumber * ((int)(n1 * m2) / numberOfThreads);
            int to = from + ((int)(n1 * m2) / numberOfThreads) - 1;
            int line, column, result;

            for (int j = from; j <= to; ++j) {
                line = (int)j / m2;
                column = j % m2;
                result = 0;
                for (int k = 0; k < m1; ++k)
                    result += matrix1copy[line][k] * matrix2[k][column];
                productResult[line][column] = result;
            }

            return true;
        }
    }


    public static void main(String[] args) throws FileNotFoundException, ExecutionException, InterruptedException {
        File file =
                new File("src\\date.in");
        Scanner sc = new Scanner(file);
        n1 = sc.nextInt();
        m1 = sc.nextInt();
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < m1; ++j) {
                matrix1[i][j] = sc.nextInt();
                matrix1copy[i][j] = matrix1[i][j];
            }
        }

        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < m1; ++j) {
                System.out.print(matrix1[i][j]);
            }
            System.out.println();
        }

        n2 = sc.nextInt();
        m2 = sc.nextInt();
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < m1; ++j) {
                matrix2[i][j] = sc.nextInt();
            }
        }

        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < m2; ++j) {
                System.out.print(matrix2[i][j]);
            }
            System.out.println();
        }
        long start = System.currentTimeMillis( );
        if (PRODUCT) {
            ExecutorService service = Executors.newFixedThreadPool(numberOfThreads);
            List<Callable<Boolean>> taskList = new ArrayList<>();
            for (int i = 0; i < numberOfThreads; ++i) {
                taskList.add(new Product(i));
            }

            int remainingFrom = (numberOfThreads - 1) * ((int)(n1 * m2) / numberOfThreads) + ((int)(n1 * m2) / numberOfThreads);
            int line, column, result;
            for (int j = remainingFrom; j < n1 * m2; ++j) {
                line = (int)j / m2;
                column = j % m2;
                result = 0;
                for (int k = 0; k < m1; ++k)
                    result += matrix1copy[line][k] * matrix2[k][column];
                productResult[line][column] = result;
            }
            List<Future<Boolean>> results = service.invokeAll(taskList);
            System.out.println("Resuled product matrix is: ");

            for (int k = 0; k < n1; ++k) {
                for (int l = 0; l < m2; ++l) {
                    System.out.print(productResult[k][l]);
                    System.out.print(" ");
                }
                System.out.println();
            }
        }
        else {
            ExecutorService executor = Executors.newFixedThreadPool(numberOfThreads);
            for (int i = 0; i < numberOfThreads; ++i) {
                Sum task = new Sum(i);
                futures.add(executor.submit(task));
            }
            int remainingFrom = (numberOfThreads - 1) * ((int)(n1 * m1) / numberOfThreads) + ((int)(n1 * m1) / numberOfThreads);
            int line, column, result;

            for (int j = remainingFrom; j < n1 * m1; ++j) {
                line = (int)j / m1;
                column = j % m1;
                matrix1[line][column] += matrix2[line][column];
            }
            for (int i = 0; i < numberOfThreads; ++i) {
                futures.get(i).get();
            }
            System.out.println("Resuled sum matrix is: ");

            for (int k = 0; k < n2; ++k) {
                for (int l = 0; l < m2; ++l) {
                    System.out.print(matrix1[k][l]);
                    System.out.print(" ");
                }
                System.out.println();
            }

        }
        long end = System.currentTimeMillis( );
        System.out.print((end - start) * 0.001);
    }
}
