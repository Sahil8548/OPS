class HotelStack {
    int[] stack;
    int top;
    int size;

    HotelStack(int size) {
        this.size = size;
        stack = new int[size];
        top = -1;
    }

    void placeOrder(int orderId) {
        if (top == size - 1) {
            System.out.println("Orders full");
            return;
        }
        stack[++top] = orderId;
        System.out.println("Order placed: " + orderId);
    }

    void serveOrder() {
        if (top == -1) {
            System.out.println("No orders");
            return;
        }
        System.out.println("Order served: " + stack[top--]);
    }

    void showOrders() {
        if (top == -1) {
            System.out.println("No pending orders");
            return;
        }
        for (int i = top; i >= 0; i--) {
            System.out.print(stack[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        HotelStack hotel = new HotelStack(5);

        hotel.placeOrder(101);
        hotel.placeOrder(102);
        hotel.placeOrder(103);

        hotel.showOrders();
        hotel.serveOrder();
        hotel.showOrders();
    }
}
