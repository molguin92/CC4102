package cc4102.tarea3.olguin_romero;

import java.io.*;
import java.util.*;

/**
 * Created by arachnid92 on 16-12-15.
 */
public class Tests {

    BinarySearchTree bst;
    SplayTree splay;
    AVLTree avl;
    VEBTree veb;

    List<Integer> input1;
    List<Integer> input2;

    public Tests(){
        this.input1 = new ArrayList<>();
        this.input2 = new ArrayList<>();

        //read files:
        try (BufferedReader br = new BufferedReader(new FileReader("./input1.out"))) {
            String line;
            int in;
            while ((line = br.readLine()) != null) {
                in = Integer.parseInt(line);
                this.input1.add(in);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (BufferedReader br = new BufferedReader(new FileReader("./input2.out"))) {
            String line;
            int in;
            while ((line = br.readLine()) != null) {
                in = Integer.parseInt(line);
                this.input2.add(in);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.err.println("input1: " + input1.size());
        System.err.println("input2: " + input2.size());

    }

    private static void put(Tree tree, Integer[] input)
    {
        for(int i: input)
            tree.put(i, null);
    }

    private static void delete(Tree tree, Integer[] input)
    {
        for(int i: input)
            tree.delete(i);
    }

    private void InsertDeleteAllOrdered() throws FileNotFoundException, UnsupportedEncodingException {

        Collections.sort(input1);
        Collections.sort(input2);

        this.InsertDelete("ordered_", false);
    }

    private void InsertDeleteAllRandom() throws FileNotFoundException, UnsupportedEncodingException {

        Collections.shuffle(input1);
        Collections.shuffle(input2);

        this.InsertDelete("random_", true);
    }

    void run()
    {
        try {
            this.InsertDeleteAllOrdered();
            this.InsertDeleteAllRandom();
            this.InsertAndSearchExistent();
            this.InsertAndSearchRandom();
            this.InsertAndSearchOneExistentElement();
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args)
    {
        Tests t = new Tests();
        t.run();
    }

    public void InsertDelete(String file_prefix, boolean random) throws FileNotFoundException, UnsupportedEncodingException {
        Integer[] ainput1 = input1.toArray(new Integer[input1.size()]);
        Integer[] ainput2 = input2.toArray(new Integer[input2.size()]);
        Tree tree;

        PrintWriter writer = new PrintWriter("./" + file_prefix + "input_delete_universe1.csv", "UTF-8");
        writer.println("structure, operation, time(ns)");


        // input 1
        for(int i = 0; i < 200; i++)
        {
            //BST
            tree = new BinarySearchTree();
            long ti = System.nanoTime();
            put(tree, ainput1);
            long tf = System.nanoTime();
            writer.println("bst, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput1));

            ti = System.nanoTime();
            delete(tree, ainput1);
            tf = System.nanoTime();
            writer.println("bst, delete, " + (tf-ti));


            //AVL
            tree = new AVLTree();
            ti = System.nanoTime();
            put(tree, ainput1);
            tf = System.nanoTime();
            writer.println("avl, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput1));

            ti = System.nanoTime();
            delete(tree, ainput1);
            tf = System.nanoTime();
            writer.println("avl, delete, " + (tf-ti));

            //Splay
            tree = new SplayTree();
            ti = System.nanoTime();
            put(tree, ainput1);
            tf = System.nanoTime();
            writer.println("splay, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput1));

            ti = System.nanoTime();
            delete(tree, ainput1);
            tf = System.nanoTime();
            writer.println("splay, delete, " + (tf-ti));

            //vEB
            VEBTree t = new VEBTree((int) Math.pow(2, 16));
            ti = System.nanoTime();
            for (int a: ainput1)
                t.put(a);
            tf = System.nanoTime();
            writer.println("veb, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput1));

            ti = System.nanoTime();
            for (int a: ainput1)
                t.delete(a);
            tf = System.nanoTime();
            writer.println("veb, delete, " + (tf-ti));
        }

        writer.close();

        writer = new PrintWriter("./" + file_prefix + "input_delete_universe2.csv", "UTF-8");
        writer.println("structure, operation, time(ns)");

        // input 2
        for(int i = 0; i < 200; i++)
        {
            //BST
            tree = new BinarySearchTree();
            long ti = System.nanoTime();
            put(tree, ainput2);
            long tf = System.nanoTime();
            writer.println("bst, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput2));

            ti = System.nanoTime();
            delete(tree, ainput2);
            tf = System.nanoTime();
            writer.println("bst, delete, " + (tf-ti));


            //AVL
            tree = new AVLTree();
            ti = System.nanoTime();
            put(tree, ainput2);
            tf = System.nanoTime();
            writer.println("avl, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput2));

            ti = System.nanoTime();
            delete(tree, ainput2);
            tf = System.nanoTime();
            writer.println("avl, delete, " + (tf-ti));

            //Splay
            tree = new SplayTree();
            ti = System.nanoTime();
            put(tree, ainput2);
            tf = System.nanoTime();
            writer.println("splay, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput2));

            ti = System.nanoTime();
            delete(tree, ainput2);
            tf = System.nanoTime();
            writer.println("splay, delete, " + (tf-ti));

            //vEB
            VEBTree t = new VEBTree((int) Math.pow(2, 26));
            ti = System.nanoTime();
            for (int a: ainput2)
                t.put(a);
            tf = System.nanoTime();
            writer.println("veb, put, " + (tf-ti));

            if(random)
                Collections.shuffle(Arrays.asList(ainput2));

            ti = System.nanoTime();
            for (int a: ainput2)
                t.delete(a);
            tf = System.nanoTime();
            writer.println("veb, delete, " + (tf-ti));
        }

        writer.close();
    }

    public long benchmarkInsertAndSearch(Tree tree, int n_insert, Integer[] search, Integer[] input ) {

        for(int i = 0; i < n_insert; i++)
            tree.put(input[i], null);

        long ti = System.nanoTime();
        for(Integer i: search)
            tree.get(i);
        long tf = System.nanoTime();

        return tf - ti;
    }

    public long benchmarkInsertAndSearch(VEBTree tree, int n_insert, Integer[] search, Integer[] input ) {

        for(int i = 0; i < n_insert; i++)
            tree.put(input[i]);

        long ti = System.nanoTime();
        for(Integer i: search)
            tree.contains(i);
        long tf = System.nanoTime();

        return tf - ti;
    }

    public void InsertAndSearchExistent() throws FileNotFoundException, UnsupportedEncodingException {
        Collections.shuffle(input1);
        Collections.shuffle(input2);

        ArrayList<Integer> search1 = new ArrayList<>();
        ArrayList<Integer> search2 = new ArrayList<>();

        for(Integer i: input1)
        {
            search1.add(i);
            if(search1.size() == 1000) break;
        }

        for(Integer i: input2)
        {
            search2.add(i);
            if(search2.size() == 1000) break;
        }

        Collections.shuffle(input1);
        Collections.shuffle(input2);

        Integer[] ainput1 = input1.toArray(new Integer[input1.size()]);
        Integer[] ainput2 = input2.toArray(new Integer[input2.size()]);
        Tree tree;

        PrintWriter writer = new PrintWriter("./search_existent_universe1.csv", "UTF-8");
        writer.println("structure, size, time(ns)");

        // input 1
        for(int i = 0; i < 200; i++)
        {
            // BST
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new BinarySearchTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("bst, 2^%d, %d\n", exp, t);
            }

            // AVL
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new AVLTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("avl, 2^%d, %d\n", exp, t);
            }

            // Splay
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new SplayTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("splay, 2^%d, %d\n", exp, t);
            }

            // VEB
            for(int exp = 8; exp < 12; exp++)
            {
                VEBTree v = new VEBTree((int) Math.pow(2, 26));
                long t = benchmarkInsertAndSearch(v, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("veb, 2^%d, %d\n", exp, t);
            }

        }

        writer.close();

        writer = new PrintWriter("./search_existent_universe2.csv", "UTF-8");
        writer.println("structure, size, time(ns)");

        // input 2
        for(int i = 0; i < 200; i++)
        {
            // BST
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new BinarySearchTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("bst, 2^%d, %d\n", exp, t);
            }

            // AVL
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new AVLTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("avl, 2^%d, %d\n", exp, t);
            }

            // Splay
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new SplayTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("splay, 2^%d, %d\n", exp, t);
            }

            // VEB
            for(int exp = 6; exp < 10; exp++)
            {
                VEBTree v = new VEBTree((int) Math.pow(2, 26));
                long t = benchmarkInsertAndSearch(v, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("veb, 2^%d, %d\n", exp, t);
            }

        }

        writer.close();
    }

    public void InsertAndSearchOneExistentElement() throws FileNotFoundException, UnsupportedEncodingException {
        Collections.shuffle(input1);
        Collections.shuffle(input2);

        Integer[] search1 = new Integer[1000];
        Integer[] search2 = new Integer[1000];

        Arrays.fill(search1, input1.get(0));
        Arrays.fill(search2, input2.get(0));

        Collections.shuffle(input1);
        Collections.shuffle(input2);

        Integer[] ainput1 = input1.toArray(new Integer[input1.size()]);
        Integer[] ainput2 = input2.toArray(new Integer[input2.size()]);
        Tree tree;

        PrintWriter writer = new PrintWriter("./search_oneelement_universe1.csv", "UTF-8");
        writer.println("structure, size, time(ns)");

        // input 1
        for(int i = 0; i < 200; i++)
        {
            // BST
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new BinarySearchTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1, ainput1);
                writer.printf("bst, 2^%d, %d\n", exp, t);
            }

            // AVL
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new AVLTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1, ainput1);
                writer.printf("avl, 2^%d, %d\n", exp, t);
            }

            // Splay
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new SplayTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1, ainput1);
                writer.printf("splay, 2^%d, %d\n", exp, t);
            }

            // VEB
            for(int exp = 8; exp < 12; exp++)
            {
                VEBTree v = new VEBTree((int) Math.pow(2, 26));
                long t = benchmarkInsertAndSearch(v, (int)Math.pow(2, exp), search1, ainput1);
                writer.printf("veb, 2^%d, %d\n", exp, t);
            }

        }

        writer.close();

        writer = new PrintWriter("./search_oneelement_universe2.csv", "UTF-8");
        writer.println("structure, size, time(ns)");

        // input 2
        for(int i = 0; i < 200; i++)
        {
            // BST
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new BinarySearchTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2, ainput2);
                writer.printf("bst, 2^%d, %d\n", exp, t);
            }

            // AVL
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new AVLTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2, ainput2);
                writer.printf("avl, 2^%d, %d\n", exp, t);
            }

            // Splay
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new SplayTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2, ainput2);
                writer.printf("splay, 2^%d, %d\n", exp, t);
            }

            // VEB
            for(int exp = 6; exp < 10; exp++)
            {
                VEBTree v = new VEBTree((int) Math.pow(2, 26));
                long t = benchmarkInsertAndSearch(v, (int)Math.pow(2, exp), search2, ainput2);
                writer.printf("veb, 2^%d, %d\n", exp, t);
            }

        }

        writer.close();
    }

    public void InsertAndSearchRandom() throws FileNotFoundException, UnsupportedEncodingException {
        Collections.shuffle(input1);
        Collections.shuffle(input2);

        ArrayList<Integer> search1 = new ArrayList<>();
        ArrayList<Integer> search2 = new ArrayList<>();
        Random rnd = new Random(System.nanoTime());

        while (search1.size() < 1000)
        {
            int i = rnd.nextInt((int) Math.pow(2, 12));
            search1.add(i);
        }

        while (search2.size() < 1000)
        {
            int i = rnd.nextInt((int) Math.pow(2, 10));
            search2.add(i);
        }

        Collections.shuffle(input1);
        Collections.shuffle(input2);
        Collections.shuffle(search1);
        Collections.shuffle(search2);

        Integer[] ainput1 = input1.toArray(new Integer[input1.size()]);
        Integer[] ainput2 = input2.toArray(new Integer[input2.size()]);
        Tree tree;

        PrintWriter writer = new PrintWriter("./search_random_universe1.csv", "UTF-8");
        writer.println("structure, size, time(ns)");

        // input 1
        for(int i = 0; i < 200; i++)
        {
            // BST
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new BinarySearchTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("bst, 2^%d, %d\n", exp, t);
            }

            // AVL
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new AVLTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("avl, 2^%d, %d\n", exp, t);
            }

            // Splay
            for(int exp = 8; exp < 12; exp++)
            {
                tree = new SplayTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("splay, 2^%d, %d\n", exp, t);
            }

            // VEB
            for(int exp = 8; exp < 12; exp++)
            {
                VEBTree v = new VEBTree((int) Math.pow(2, 26));
                long t = benchmarkInsertAndSearch(v, (int)Math.pow(2, exp), search1.toArray(new Integer[0]), ainput1);
                writer.printf("veb, 2^%d, %d\n", exp, t);
            }

        }

        writer.close();

        writer = new PrintWriter("./search_random_universe2.csv", "UTF-8");
        writer.println("structure, size, time(ns)");

        // input 2
        for(int i = 0; i < 200; i++)
        {
            // BST
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new BinarySearchTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("bst, 2^%d, %d\n", exp, t);
            }

            // AVL
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new AVLTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("avl, 2^%d, %d\n", exp, t);
            }

            // Splay
            for(int exp = 6; exp < 10; exp++)
            {
                tree = new SplayTree();
                long t = benchmarkInsertAndSearch(tree, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("splay, 2^%d, %d\n", exp, t);
            }

            // VEB
            for(int exp = 6; exp < 10; exp++)
            {
                VEBTree v = new VEBTree((int) Math.pow(2, 26));
                long t = benchmarkInsertAndSearch(v, (int)Math.pow(2, exp), search2.toArray(new Integer[0]), ainput2);
                writer.printf("veb, 2^%d, %d\n", exp, t);
            }

        }

        writer.close();
    }
}
