package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.AVLTree;
import cc4102.tarea3.olguin_romero.Node;
import org.junit.After;
import org.junit.Before;

import static org.junit.Assert.*;

/**
 * Created by arachnid92 on 06-12-15.
 */
public class AVLTest extends TreeTest {

    boolean isAVL;
    int height;

    @Before
    public void setUp() throws Exception {
        tree = new AVLTree();
        populate();
        isAVL = true;
        height = 0;
    }

    @After
    public void tearDown() throws Exception {
        assertIsAVL();
    }

    @org.junit.Test
    @Override
    public void testDelete() throws Exception
    {
        // TODO: Fix
        assertEquals(initsize, tree.size());

        for(int i = 0; i < initsize; i++)
        {
            String key = Integer.toString(i);
            System.err.println("Deleting " + key);
            tree.delete(key);
            assertIsAVL();
            assertEquals(initsize - i - 1, tree.size());
            assertEquals(null, tree.get(key));
        }
    }

    protected void assertIsAVL()
    {
        Node root = tree.getRoot();
        height = getHeight(root);
    }

    protected int getHeight(Node node)
    {
        if (node == null) {
            return -1;
        }
        else
        {
            int hl = getHeight(node.left);
            int hr = getHeight(node.right);

            if(Math.abs(hl - hr) > 1) throw new AssertionError("Not AVLTree. Left: " + hl + " Right: " + hr);

            int h = Math.max(hl, hr) + 1;
            return h;
        }
    }
}