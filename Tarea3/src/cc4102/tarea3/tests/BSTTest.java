package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.BST;

import java.util.Random;

import static org.junit.Assert.*;

/**
 * Created by arachnid92 on 06-12-15.
 */
public class BSTTest {

    private static int initsize = 256;

    BST bst;

    @org.junit.Before
    public void setUp() throws Exception {
        bst = new BST();
        populate();
    }

    private void populate()
    {
        for(int i = 0; i < initsize; i++)
        {
            String kv = Integer.toString(i);
            bst.put(kv, kv);
        }

    }

    @org.junit.After
    public void tearDown() throws Exception {

    }

    @org.junit.Test
    public void testPut() throws Exception {
        assertEquals(initsize, bst.size());
        bst.put("new key", "new value");
        assertEquals(initsize + 1, bst.size());
    }

    @org.junit.Test
    public void testGet() throws Exception {
        assertEquals(initsize, bst.size());

        for(int i = 0; i < initsize; i++)
        {
            String key = Integer.toString(i);
            String value = bst.get(key);
            assertEquals(key, value);
        }
    }

    @org.junit.Test
    public void testDelete() throws Exception {
        assertEquals(initsize, bst.size());

        for(int i = 0; i < initsize; i++)
        {
            String key = Integer.toString(i);
            bst.delete(key);
            assertEquals(bst.size(), initsize - i - 1);
        }
    }
}