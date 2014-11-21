import java.util.ArrayList;
import java.util.Iterator;

public class SSTF {

	private int h = 0;
	private int nh = 0;
	private ArrayList<Integer> r;
	private ArrayList<Integer> seq = new ArrayList<Integer>();
	private boolean running;

	public SSTF(int head, ArrayList<Integer> requests) {
		h = head;
		r = new ArrayList<Integer>(requests);
		running = true;
	}

	public void run() {		
		nh = this.h;
		seq.add(nh);

		while (running) {
			int tmp2 = 0;
			int cnt = 0;
			int tmp = 0;
			int min = -1;
			int min_val = 0;
			
			for (Integer x : this.r) {
				tmp = Math.abs(x - nh);
				if (tmp < min || min == -1) {
					min = tmp;
					min_val = x;
					tmp2 = cnt;
				}
				cnt++;
			}
			if (this.r.size() == 0) {
				running = false;
			} else {
				this.r.remove(tmp2);
				nh = min_val;
				seq.add(min_val);
				min = -1;
			}
		}
		
		display();
	}

	private void display() {
		int tmp = 0;
		int cnt = 0;
		int total = 0;
		
		System.out.print("Disk head pos: ");
		
		for (Integer x: seq) {
			if (cnt == 0) {
				System.out.print(x + " -> ");
				tmp = x;
				cnt++;
			} else if (cnt != seq.size() - 1) {
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
