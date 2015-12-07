package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.AVL;
import cc4102.tarea3.olguin_romero.Node;
import org.junit.After;
import org.junit.Before;

import static org.junit.Assert.*;

/**
 * Created by arachnid92 on 06-12-15.
 */
public class AVLTest extends TreeTest {

    boolean isAVL;

    @Before
    public void setUp() throws Exception {
        tree = new AVL();
        populate();
        isAVL = true;
    }

    @org.junit.Test
    @Override
    public void testPut() throws Exception {
        super.testPut();
        testIsAVL();
    }

    @org.junit.Test
    @Override
    public void testGet() throws Exception {
        super.testGet();
        testIsAVL();
    }

    @org.junit.Test
    @Override
    public void testDelete() throws Exception {
        super.testDelete();
        testIsAVL();
    }

    protected void testIsAVL()
    {
        Node root = tree.getRoot();
        int height = getHeight(root);
        assertTrue(isAVL);
    }

    protected int getHeight(Node node)
    {
        if (node == null)
            return -1;
        else
        {
            int hl = getHeight(node.left);
            int hr = getHeight(node.right);

            if(Math.abs(hl - hr) > 1) this.isAVL = false;

            return Math.max(hl, hr);
        }
    }
}