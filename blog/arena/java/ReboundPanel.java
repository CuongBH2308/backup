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
 *  ��ʾ���ʹ��Timer ����������Swing�Ķ���Ч����
 * @author guanminglin <guanminglin@gmail.com>
 */
public class ReboundPanel extends JPanel {

    private final int panelWidth = 300, panelHeight = 200;
    private final int DELAY = 20, IMAGE_SIZE = 35;
    private ImageIcon image;
    private Timer timer;
    private int x, y, moveX, moveY;

    /**
     * ��幹�캯������ʼ����塣����Timer �ĳ�����
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
     *  ���ͼ��������е�λ�á�
     * @param page
     */
    @Override
    public void paintComponent(Graphics page) {
        super.paintComponent(page);
        image.paintIcon(this, page, x, y);
       
    }

    //Swing ���������ϵĸ���ͼ���λ�ã��Ѵﵽ������Ч����
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