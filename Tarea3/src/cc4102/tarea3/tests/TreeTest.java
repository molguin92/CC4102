package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.Tree;

import static org.junit.Assert.assertEquals;

/**
 * Created by arachnid92 on 06-12-15.
 */
public abstract class TreeTest {

    public static int initsize = 256;
    Tree tree;

    @org.junit.Before
    public abstract void setUp() throws Exception;

    public void populate()
    {
        for(int i = 0; i < initsize; i++)
        {
            String kv = Integer.toString(i);
            tree.put(i, kv);
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

        for(int i = 0; i < initsize; i++)
        {
            String key = Integer.toString(i);
            String value = tree.get(key);
            assertEquals(key, value);
        }
    }

    @org.junit.Test
    public void testDelete() throws Exception {
        assertEquals(initsize, tree.size());

        for(int i = 0; i < initsize; i++)
        {
            String key = Integer.toString(i);
            tree.delete(key);
            assertEquals(initsize - i - 1, tree.size());
            assertEquals(null, tree.get(key));
        }
    }

}
