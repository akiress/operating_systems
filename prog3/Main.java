import java.util.ArrayList;

public class Main {

	private static int head = 0;
	private static int max_cylinders = 0;
	private static ArrayList<Integer> requests = new ArrayList<Integer>();

	public Main() {
	}

	public static void main(String[] args) {
		try {
			if (args.length != 3) {
				System.out
						.println("Usage: main <head> <max # cylinders> <requests ex: [1,2,3]>");
			} else {
				head = Integer.parseInt(args[0]);
				max_cylinders = Integer.parseInt(args[1]);

				convert_sequence(args[2]);
				
				System.out.println("FCFS");
				FCFS fcfs = new FCFS(head, requests);
				fcfs.run();
				newline();
				
				System.out.println("SSTF");
				SSTF sstf = new SSTF(head, requests);
				sstf.run();
				newline();
				
				System.out.println("CSCAN");
				CSCAN cscan = new CSCAN(head, max_cylinders, requests);
				cscan.run();
				newline();
				
				System.out.println("CLOOK");
				CLOOK clook = new CLOOK(head, requests);
				clook.run();
				newline();
			}
		} catch (NumberFormatException nfe) {
			System.out.println(nfe.getMessage());
		} catch (NullPointerException npe) {
			System.out.println(npe.getMessage());
		}
	}

	private static void newline() {
		System.out.println("\n");
	}

	public static ArrayList<Integer> convert_sequence(String str) {
		String tmp = str.replace("[", "");
		tmp = tmp.replace("]", "");
		String[] tmp2 = tmp.split(",");
		for (String s : tmp2) {
			Integer x = Integer.parseInt(s);
			if (x != null) {
				requests.add(x);
			}
		}

		return requests;
	}
}
