package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.Tree;

import java.util.HashSet;
import java.util.Random;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

/**
 * Created by arachnid92 on 06-12-15.
 */
public abstract class TreeTest {

    public static int initsize = 256;
    Tree tree;
    HashSet<Integer> set;

    @org.junit.Before
    public abstract void setUp() throws Exception;

    public void populate()
    {
        set = new HashSet<>(initsize);
        Random r = new Random(System.nanoTime());
        while (set.size() < initsize)
        {
            int entry = r.nextInt(initsize);
            if(!set.contains(entry))
            {
                set.add(entry);
                tree.put(entry, entry + "");
            }
        }
    }

    @org.junit.Test
    public void testPut() throws Exception {
        assertEquals(initsize, tree.size());
        tree.put(8000, "new value");
        assertEquals(initsize + 1, tree.size());
    }

    @org.junit.Test
    public void testGet() throws Exception {
        assertEquals(initsize, tree.size());

        for(int i: set)
        {
            String value = tree.get(i);
            assertEquals(Integer.toString(i), value);
        }

        assertEquals(null, tree.get(12334));
    }

    @org.junit.Test
    public void testDelete() throws Exception {
        assertEquals(initsize, tree.size());

        for(int i: set)
        {
            tree.delete(i);
            assertEquals(null, tree.get(i));
            //assertEquals(initsize - i - 1, tree.size());
        }
    }

}
