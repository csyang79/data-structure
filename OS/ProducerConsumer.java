public class ProducerConsumer {
	private static Integer count = 0;
	private static final Integer FULL = 10;
	private static Object LOCK = "lock";

	public static void main(String[] args) {
		ProducerConsumer test = new ProducerConsumer();
		new Thread(test.new Producer()).start();
		new Thread(test.new Consumer()).start();
		new Thread(test.new Producer()).start();
		new Thread(test.new Consumer()).start();
		new Thread(test.new Producer()).start();
		new Thread(test.new Consumer()).start();
		new Thread(test.new Producer()).start();
		new Thread(test.new Consumer()).start();
		new Thread(test.new Producer()).start();
		new Thread(test.new Consumer()).start();
	}

	class Producer implements Runnable {
		@Override
		public void run() {
			for (int i = 0; i < 10; ++i) {
				try {
					Thread.sleep(3000);
				}
				catch (Exception e) {
					e.printStackTrace();
				}
				synchronized(LOCK) {
					while (count == FULL) {
						try {
							LOCK.wait();
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
					++count;
					System.out.println(Thread.currentThread().getName() + "生产者生产，目前个数：" + count);
					LOCK.notifyAll();
				}
			}
		}
	}

	class Consumer implements Runnable {
		@Override
			public void run() {
				for (int i = 0; i < 10; ++i) {
					try  {
						Thread.sleep(3000);
					} catch (Exception e) {
						e.printStackTrace();
					}
					synchronized(LOCK) {
						while (count == 0) {
							try {
								LOCK.wait();
							} catch (Exception e) {
								e.printStackTrace();
							}
						}
						--count;
						System.out.println(Thread.currentThread().getName() + "消费者消费，目前个数： " + count);
						LOCK.notifyAll();
					}
				}
			}
	}
}
