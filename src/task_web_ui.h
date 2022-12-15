/** @file task_web_ui.h
 *  This file contains the headers for a web server user interface task. It 
 *  serves a static web page that is used for the balancing cube project.
 * 
 *  @author Juan Luna
 *  @date   2022-Nov-30
 */

#include <Arduino.h>
#include "PrintStream.h"
#include <WiFi.h>
#include <WebServer.h>
#include "shares.h"

// Task function implementing web user interface functionality
void task_webserver(void* p_params);
// Set up WiFi
void setup_wifi(void);
// Put a web page header into an HTML string
void HTML_header(String& a_string, const char* page_title);
// Callback function that responds to HTTP requests without a subpage name
void handle_DocumentRoot();
// Respond to a request for an HTTP page that doesn't exist
void handle_NotFound (void);
// Toggle blue LED when called by the web server. Used for testing.
void handle_Toggle (void);