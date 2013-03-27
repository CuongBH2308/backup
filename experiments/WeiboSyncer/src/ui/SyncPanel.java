package ui;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

import wb.WeiboSyncer;
import weibo4j.model.WeiboException;

public class SyncPanel extends JPanel {

	private JLabel _inputCodeLabel;
	private JButton _getCodeButton;
	private JTextField _codeField;
	
	private JLabel _inputDb;
	private JTextField _dbField;
	
	private JButton _syncButton;
	
	private WeiboSyncer _syncer = new WeiboSyncer();
	
	
	private void AddComponent(JComponent comp, int x, int y, int width, Insets insets)
	{
		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.HORIZONTAL;
		//c.fill = GridBagConstraints.BOTH;
		c.gridwidth = width;
		c.insets = insets;  //top padding
		c.gridx = x;
		c.gridy = y;
		this.add(comp, c);
	}
	/**
	 * Create the panel.
	 */
	public SyncPanel() {
		this.setBorder(new EmptyBorder(5, 5, 5, 5));
		this.setLayout(new GridBagLayout());
		
		// Input access code
		_inputCodeLabel = new JLabel("请输入访问代码:");
		AddComponent(_inputCodeLabel, 0, 0, 1, new Insets(0,0,0,5));
		
		_getCodeButton = new JButton("获取代码");
		AddComponent(_getCodeButton, 1, 0, 1, new Insets(0,0,0,0));
		
		_codeField = new JTextField();
		_codeField.setColumns(80);
		AddComponent(_codeField, 0, 1, 2, new Insets(3,0,0,0));
		

		// Input database
		_inputDb = new JLabel("请输入数据库文件:");
		AddComponent(_inputDb, 0, 2, 1, new Insets(20,0,0,0));
		
		_dbField = new JTextField();
		_dbField.setColumns(80);
		AddComponent(_dbField, 0, 3, 2, new Insets(0,0,0,0));
		
		
		// Sync
		_syncButton = new JButton("开始同步");
		AddComponent(_syncButton, 0, 4, 2, new Insets(30,0,0,0));
		
		
		
		// Add event handler
		_getCodeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {

					_syncer.getAccessCodeFromBrowser();

				} catch (WeiboException ex) {
					// TODO Auto-generated catch block
					ex.printStackTrace();
				}

			}
		});
		
		_syncButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {

					// Verify the input
					String accessCode = _codeField.getText();
					String database = _dbField.getText();

					_syncer.sync(accessCode, database);

				} catch (Exception ex) {
					// TODO Auto-generated catch block
					ex.printStackTrace();
				}

			}
		});
		
		
	}

}
