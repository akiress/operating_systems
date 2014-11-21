import java.util.ArrayList;

public class FCFS {

	private int h = 0;
	private ArrayList<Integer> r;

	public FCFS(int head, ArrayList<Integer> requests) {
		h = head;
		r = new ArrayList<Integer>(requests);
	}

	public void run() {
		this.r.add(0, this.h);

		display();
	}

	private void display() {
		int cnt = 0;
		int total = 0;
		int tmp = 0;
		
		System.out.print("Disk head pos: ");
		
		for (Integer x : this.r) {
			if (cnt == 0) {
				System.out.print(x + " -> ");
				tmp = x;
				cnt++;
			} else if (cnt != this.r.size() - 1) {
				System.out.print(x + " -> ");
				cnt++;
				total = total + Math.abs(x - tmp);
				tmp = x;
			} else {
				System.out.print(x);
				total = total + Math.abs(x - tmp);
			}
		}

		System.out.println();
		System.out.println("Total head movement: " + total);	
	}
}
