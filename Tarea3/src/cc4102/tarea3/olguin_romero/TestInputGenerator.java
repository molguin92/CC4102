package cc4102.tarea3.olguin_romero;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.HashSet;
import java.util.Random;

/**
 * Created by arachnid92 on 16-12-15.
 */
public class TestInputGenerator {

    public static int univ_exp1 = 12;
    public static int univ_exp2 = 10;

    public static int in_exp1 = 11;
    public static int in_exp2 = 9;

    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {

        Random rnd = new Random(System.nanoTime());
        int in;

        int universe1 = (int) Math.pow(2, univ_exp1);
        int universe2 = (int) Math.pow(2, univ_exp2);

        int input_size1 = (int) Math.pow(2, in_exp1);
        int input_size2 = (int) Math.pow(2, in_exp2);

        HashSet<Integer> input1 = new HashSet<>(input_size1);
        HashSet<Integer> input2 = new HashSet<>(input_size2);

        PrintWriter writer1 = new PrintWriter("./input1.out", "UTF-8");
        PrintWriter writer2 = new PrintWriter("./input2.out", "UTF-8");

        while (input1.size() < input_size1)
        {
            in = rnd.nextInt(universe1);
            if(!input1.contains(in))
            {
                input1.add(in);
                writer1.println(in);
            }
        }

        while (input2.size() < input_size2)
        {
            in = rnd.nextInt(universe2);
            if(!input2.contains(in))
            {
                input2.add(in);
                writer2.println(in);
            }
        }


        writer1.close();
        writer2.close();
    }

}
