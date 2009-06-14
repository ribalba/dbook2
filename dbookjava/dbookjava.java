public class dbookjava {
  private native void check_isbn();
  public static void main(String[] args) {
    new dbookjava().check_isbn();
  }

  static {
    System.loadLibrary("dbookjava");
  }	
}
