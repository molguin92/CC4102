package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.Tree;
import cc4102.tarea3.olguin_romero.VEBTree;

import java.util.HashSet;
import java.util.Random;

import static org.junit.Assert.*;

/**
 * Created by arachnid92 on 09-12-15.
 */
public class VEBTreeTest {

    VEBTree tree;
    public static int initsize = 256;
    HashSet<Integer> set;

    @org.junit.Before
    public void setUp() throws Exception {
        this.tree = new VEBTree((int) Math.pow(2, 16));
        populate();
    }

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
                tree.put(entry);
            }
        }
    }

    @org.junit.Test
    public void testPut() throws Exception {

        tree.put(8000);
        assertTrue(tree.contains(8000));
    }

    @org.junit.Test
    public void testContains() throws Exception {
        for(int i: set)
        {
            assertTrue(tree.contains(i));
        }
        assertFalse(tree.contains(1234));
    }

    @org.junit.Test
    public void testDelete() throws Exception {
        Random rnd = new Random(System.nanoTime());

        while(set.size() > 0)
        {
            int item;
            do {
                item = rnd.nextInt(initsize);
            } while (!set.contains(item));

            tree.delete(item);
            set.remove(item);
            assertFalse("Item shouldnt be in tree: " + item + ". Current set size: " + set.size(), tree.contains(item));
            //assertEquals(initsize - i - 1, tree.size());
        }
    }

}