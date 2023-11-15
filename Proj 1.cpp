#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void read_and_check(int acc_number, double beginMB, double& maxMB_used,
                    double& endMB, bool& errors_detected);

bool is_valid_account_number (int acc_num);

void calculate_bill (double base_charge, double disk_limit, double max_usage,
                     double end_usage, double& over_lim_charge,
                     double& end_month_penalty, double& gst_amount,
                     double& total_amount);

void print_bill (int acc_number, double disk_limit, double beginMB, double maxMB_used,
                 double endMB, double base_charge, double over_lim_charge,
                 double end_month_penalty, double gst_amount, double total_amount);

/* The main function is responsbile for reading the input data from the file and then calling \     
  the functions in order to ensure that the monthly bill is accurately calculated. */
int main() {
  int account_number;
  double base_charge, disk_limit, beginMB, maxMB_used, endMB;
  bool errors_detected = false;
  char valid_flag;

  cin >> account_number >> base_charge >> disk_limit >> beginMB >> maxMB_used >> endMB;
  cin >> valid_flag;

    if (valid_flag == 'F') {
    cout << "Invalid account number " << account_number << " found" << endl;
    cout << "Bad monthly transaction record" << endl;
    cout << " *** Account " << account_number << " not processed due to errors ***" << endl;

    /* The if statements are used to ensuure that the function continues to run normally after the \
validity of the coustomers information is confirmed from the valid flag. */

  }
  else if (valid_flag == 'T') {
  read_and_check(account_number, beginMB, maxMB_used, endMB, errors_detected);
  if (!errors_detected) {
    double over_lim_charge, end_month_penalty, gst_amount, total_amount;
    calculate_bill(base_charge, disk_limit, maxMB_used, endMB, over_lim_charge, end_month_penalty,
                   gst_amount, total_amount);
    print_bill(account_number, disk_limit, beginMB, maxMB_used, endMB, base_charge,
               over_lim_charge, end_month_penalty, gst_amount, total_amount);
  }
  }
  return 0;
}

/* This function is responsible for checking if the account number that the coustomer has provided \
is a valid account number based on specific rules. */

bool is_valid_account_number (int acc_num){
  if (acc_num < 100000 || acc_num > 999999) {
    return false;}
  //checks if the account number is exactly 6 digits long                                           

    int units_dig = acc_num % 10;
    int remaining_digits = acc_num / 10;
    int position = 5;

    int sum = 0;
    while (remaining_digits > 0) {
      int digit = remaining_digits % 10;
      sum += digit * position;
      remaining_digits /= 10;
      position++;
    }
    int checkDigit = sum % 10;
    return (checkDigit == units_dig);
    /* Checking if the check degit number is equivalent to the units dight of the sum of the \      
       remaining digits multipled by their respecitive positon to ensure validity. */

}
/* This function is responsbile for reading and updating the valid flag then printing out the \     
  corresponding error messages if required. */

void read_and_check(int acc_number, double beginMB, double& maxMB_used,
                    double& endMB, bool& errors_detected){
  char valid_flag;
  cin >> valid_flag; // Read 'T' or 'F' for errors_detected                                         

  if (valid_flag == 'F') {
    cout << "Bad monthly transaction record" << endl;
    errors_detected = true;}
  else  if (valid_flag == 'T') {
    errors_detected = false;}

  if (!is_valid_account_number(acc_number)){
    cout << "Invalid account number " << acc_number << " found" << endl;
    cout << " *** Account " << acc_number << " not processed due to errors ***" << endl;
    errors_detected = true;
    return;
  }
}

/* This function is the function that calcluates the exact values for the amount of payment the \   
   coustomer will have on their monthly bill. */
void calculate_bill (double base_charge, double disk_limit, double max_usage,
                     double end_usage, double& over_lim_charge,
                     double& end_month_penalty, double& gst_amount,
                     double& total_amount) {

  cin >> base_charge;

  //Calculating the over limit surcharge                                                            
  double over_limit = max_usage - disk_limit;over_lim_charge = 0.0;

  if (over_limit > 0) {
    if (over_limit <= 50.0) {
      over_lim_charge = over_limit * 0.15;}
    else if (over_limit <= 250.0) {
      over_lim_charge = 50.0 * 0.15 + (over_limit - 50.0) * 0.26;}
    else if (over_limit <= 500.0) {
      over_lim_charge = (50.0 * 0.15) + (200.0 * 0.26) + (over_limit -250.0) * 0.37;}
    else {
      over_lim_charge = (50.0 * 0.15) + (200.0 * 0.26) + (250.0 * 0.37) +
        (over_limit - 500.0) * 0.48; }
  }

  //Calculate end of month penalty-surcharge                                                        
  double excess_usage = end_usage - disk_limit;
  end_month_penalty = 0.0; // initialize the charge to 0                                            

  if (excess_usage > 0) {
    double surcharge = excess_usage * 0.05;
    if (surcharge < 5.0) {
      surcharge = 5.0;
    }
    end_month_penalty = surcharge;
  }

  // Calculate the GST                                                                              
  gst_amount = (base_charge + over_lim_charge + end_month_penalty) * 0.05;
  // Calculate the total amount                                                                     
  total_amount = base_charge + over_lim_charge + end_month_penalty + gst_amount;
}
/*Print the bill with the proper precision and decimals.                                            
https://www.simplilearn.com/tutorials/cpp-tutorial/cpp-setprecision Used for setprecision guidence  
https://www.simplilearn.com/tutorials/cpp-tutorial/setw-cpp Used for setwidth guidance */

void print_bill (int acc_number, double disk_limit, double beginMB, double maxMB_used,
                 double endMB, double base_charge, double over_lim_charge,
                 double end_month_penalty, double gst_amount, double total_amount) {
  cout << fixed << setprecision(3);

  cout << "Account Number:        " << setw(8) << acc_number << endl;
  cout << endl;
  cout << "Disk Allotment:        " << setw(8) << disk_limit << " MB" << endl;
  cout << "Beginning of Month:    " << setw(8) << beginMB << " MB" << endl;
  cout << "Maximum during Month:  " << setw(8) << maxMB_used << " MB" << endl;
  cout << "End of Month:          " << setw(8) << endMB << " MB" << endl;
  cout << endl;

  cout << fixed << setprecision(2);

  cout << "Base Charge:           " << setw(8) << base_charge << endl;
  // Print Penalty surcharge if end_month_penalty is greater then 0                                 
  cout << "Over-limit Surcharge:  " << setw(8) << over_lim_charge << endl;
  if (end_month_penalty > 0) {
    cout << "Penalty surcharge:     " << setw(8) << end_month_penalty << endl;
  }
  cout << "GST:                   " << setw(8) << gst_amount << endl;
 cout << "Amount Due:           $" << setw(8) << total_amount << endl;
}



