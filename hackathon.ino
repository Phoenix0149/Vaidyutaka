#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the structure for a patient
struct Patient {
    char name[50];
    int room;
    int bed;
    char nurse[50]; // Nurse's name as a string
};

// Function to initialize OLED
void initOLED() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.display();
}

// Function to display all patient details on OLED
void displayPatientOnOLED(const Patient& patient) {
    display.clearDisplay();
    display.setCursor(0, 0);

    // Display patient details
    display.println("Patient Details:");
    display.printf("Name: %s\n", patient.name);
    display.printf("Room: %d\n", patient.room);
    display.printf("Bed: %d\n", patient.bed);
    display.printf("Nurse: %s\n", patient.nurse);

    display.display();
}

void setup() {
    Serial.begin(115200);

    // Initialize OLED
    initOLED();

    // Define the patient database
    struct Patient patients[] = {
        {"Ashu", 1, 1, "Nurse1"},
        {"Hargun", 1, 2, "Nurse1"},
        {"Disha", 1, 3, "Nurse2"},
        {"Jai", 1, 4, "Nurse2"},
        {"Ashish", 2, 1, "Nurse3"},
        {"Vivek", 2, 2, "Nurse3"},
        {"Varda", 2, 3, "Nurse4"},
        {"Jayanti", 2, 4, "Nurse4"}
    };

    // Ask the user to enter a patient number
    Serial.println("Enter patient number (0-7):");
    while (!Serial.available()); // Wait for user input
    int patientNumber = Serial.parseInt(); // Read the patient number

    // Validate the patient number
    if (patientNumber >= 0 && patientNumber < 8) {
        // Display all details of the selected patient on OLED
        displayPatientOnOLED(patients[patientNumber]);

        // Print patient details to Serial Monitor for debugging
        Serial.println("\nPatient Details:");
        Serial.printf("Name: %s\n", patients[patientNumber].name);
        Serial.printf("Room: %d\n", patients[patientNumber].room);
        Serial.printf("Bed: %d\n", patients[patientNumber].bed);
        Serial.printf("Nurse: %s\n", patients[patientNumber].nurse);
    } else {
        Serial.println("Invalid patient number! Please enter a number between 0 and 7.");
    }
}

void loop() {
    // Nothing to do here
}