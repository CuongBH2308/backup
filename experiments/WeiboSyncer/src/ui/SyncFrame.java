package ui;

import java.awt.EventQueue;

import javax.swing.JFrame;

public class SyncFrame extends JFrame {

	private SyncPanel contentPane;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					SyncFrame frame = new SyncFrame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public SyncFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 250, 250);
		contentPane = new SyncPanel();
		setContentPane(contentPane);
	}

}
