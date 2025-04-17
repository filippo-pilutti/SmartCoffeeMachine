package esiot.cmm;

public class CoffeeMachineManager {

	public static void main(String[] args) throws Exception {
		CommChannel scc = new SerialCommChannel(args[0], 9600);
		CMMgui gui = new CMMgui();
		gui.setCommChannel(scc);
		gui.start();	
		
		while(true) {
			if (scc.isMsgAvailable()) {
				String msg = scc.receiveMsg();
				if (msg.contains("Modality")) {
					gui.getLabelMode().setText(msg);
				} else if (msg.contains("Coffee")) {
					gui.getLabelCoffee().setText(msg);
				} else if (msg.contains("Tea")) {
					gui.getLabelTea().setText(msg);
				} else if (msg.contains("Chocolate")) {
					gui.getLabelChoc().setText(msg);
				} else if (msg.contains("Tests")) {
					gui.getLabelTests().setText(msg);
				}
			}
		}
	}
}
