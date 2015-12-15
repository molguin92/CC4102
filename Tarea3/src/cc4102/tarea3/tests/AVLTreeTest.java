package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.AVLTree;
import cc4102.tarea3.olguin_romero.Node;
import org.junit.After;
import org.junit.Before;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Random;

import static org.junit.Assert.*;

/**
 * Created by arachnid92 on 13-12-15.
 */
public class AVLTreeTest extends BSTTest {

    @Before
    @Override
    public void setUp() throws Exception {
        this.tree = new AVLTree();
        populate();
    }

    @Override
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
                assertIsAVL();
            }
        }
    }

    @After
    public void tearDown() throws Exception {
        super.tearDown();
        assertIsAVL();
    }

    @Override
    public void testDelete() throws Exception {
        assertEquals(initsize, tree.size());
        Integer[] all = set.toArray(new Integer[0]);
        Collections.shuffle(Arrays.asList(all));

        for (int i: all)
        {
            tree.delete(i);
            assertEquals(null, tree.get(i));
            assertIsBST();
            assertIsAVL();
            //assertEquals(initsize - i - 1, tree.size());
        }
    }

    void assertIsAVL()
    {
        Node root = tree.getRoot();
        int height = recursiveTestAVL(root);
    }

    int recursiveTestAVL(Node root)
    {
        if(root == null)
            return -1;
        else
        {
            int hl = recursiveTestAVL(root.left);
            int hr = recursiveTestAVL(root.right);

            assertTrue("Balance: " + (hl - hr) + " Node: " + root.key, Math.abs(hl - hr) < 2);
            return Math.max(hl, hr) + 1;
        }
    }
}