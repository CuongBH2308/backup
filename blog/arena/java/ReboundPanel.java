import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *  演示如何使用Timer 这个类来完成Swing的动画效果。
 * @author guanminglin <guanminglin@gmail.com>
 */
public class ReboundPanel extends JPanel {

    private final int panelWidth = 300, panelHeight = 200;
    private final int DELAY = 20, IMAGE_SIZE = 35;
    private ImageIcon image;
    private Timer timer;
    private int x, y, moveX, moveY;

    /**
     * 面板构造函数，初始化面板。包括Timer 的场景。
     */
    public ReboundPanel() {
        timer = new Timer(DELAY, new ReboundListener());
        image = new ImageIcon("images/2.jpg");
        x = 0;
        y = 40;
        moveX = moveY = 3;
        setPreferredSize(new Dimension(panelWidth, panelHeight));
        setBackground(Color.BLUE);
        timer.start();

    }

    /**
     *  绘出图像在面板中的位置。
     * @param page
     */
    @Override
    public void paintComponent(Graphics page) {
        super.paintComponent(page);
        image.paintIcon(this, page, x, y);
       
    }

    //Swing 动画，不断的更新图像的位置，已达到动画的效果。
    private class ReboundListener implements ActionListener {

        public void actionPerformed(ActionEvent e) {
            x += moveX;
            y += moveY;
            if (x <= 0 || x >= panelWidth - IMAGE_SIZE) {
                moveX = moveX * (-1);
            }
            if (y <= 0 || y >= panelHeight - IMAGE_SIZE) {
                moveY = moveY * (-1);
            }
            repaint();
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Rebound");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(new ReboundPanel());
        frame.pack();
        frame.setVisible(true);
    }
}