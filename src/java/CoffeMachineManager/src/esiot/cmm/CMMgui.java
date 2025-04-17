package esiot.cmm;
import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.*;

public class CMMgui extends JFrame {
	
	private CommChannel scc;
	
	private final JLabel lblMode;
	private final JLabel lblCoffee;
	private final JLabel lblTea;
	private final JLabel lblChoc;
	private final JLabel lblTests;

	public CMMgui() {
		
		lblMode = new JLabel("Modality: BOOT");
		lblCoffee = new JLabel("Coffee: 0");
		lblTea = new JLabel("Tea: 0");
		lblChoc = new JLabel("Chocolate: 0");
		lblTests = new JLabel("Tests: 0");
		
		JButton btnFix = new JButton("Recover");
		JButton btnRefill = new JButton("Refill");
		
		JPanel panel = new JPanel(new BorderLayout());
		JPanel panelBottom = new JPanel(new FlowLayout());
		JPanel panelTop = new JPanel(new FlowLayout());
		
		btnFix.addActionListener(e -> {
			scc.sendMsg("fix");
		});
		btnRefill.addActionListener(e -> {
			scc.sendMsg("refill");
		});
		
		panelBottom.add(btnFix);
		panelBottom.add(btnRefill);
		panel.add(panelBottom, BorderLayout.SOUTH);
		
		panelTop.add(lblMode);
		panelTop.add(lblCoffee);
		panelTop.add(lblTea);
		panelTop.add(lblChoc);
		panelTop.add(lblTests);
		panel.add(panelTop, BorderLayout.NORTH);
		
		this.getContentPane().add(panel);
		
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setSize(500, 100);
		this.setTitle("Coffee Machine Manager");
		this.setVisible(false);
		this.setResizable(false);
	}
	
	public void setCommChannel(final CommChannel cc) {
		this.scc = cc;
	}
	
	public void start() {
		JDialog boot = new JDialog();
		JLabel booting = new JLabel("System is booting...");
		boot.getContentPane().add(booting);
		boot.setLocationRelativeTo(null);
		boot.setSize(100, 100);
		boot.setTitle("Coffee Machine Manager");
		boot.setVisible(true);
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		boot.dispose();
		this.setVisible(true);
	}
	
	public JLabel getLabelMode() {
		return this.lblMode;
	}
	
	public JLabel getLabelCoffee() {
		return this.lblCoffee;
	}
	
	public JLabel getLabelTea() {
		return this.lblTea;
	}
	
	public JLabel getLabelChoc() {
		return this.lblChoc;
	}
	
	public JLabel getLabelTests() {
		return this.lblTests;
	}
	
	
	private static final long serialVersionUID = 549700488319053949L;

}
