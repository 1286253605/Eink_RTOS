#include<Arduino.h>
/* 还需要添加<style></style> */
String style_css_input_select = "input[type=\"text\"], input[type=\"password\"]{display: block;width: 200px;height: 20px;margin: 0 auto;padding: 10px;font-size: 16px;border-radius: 5px;border: none;background-color: #f1f1f1;box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);}.center-form{text-align: center;margin-top: 10px;}select {appearance: none; -moz-appearance: none;-webkit-appearance: none;border: 1px solid #ccc;border-radius: 4px;padding: 8px 16px;outline: none;font-size: 1rem;background-repeat: no-repeat;background-position: right center;background-size: 10px;cursor: pointer;width: 200px;}select::-ms-expand {display: none;}option:checked {background-color: #f0f0f0;}select:hover {border-color: #999;}";
String style_css_button = "input[type=\"submit\"] {margin-top: 10px; display: inline-block;padding: 10px 20px;font-size: 16px;font-weight: bold;color: #ffffff;background-color: #007bff;border: none;border-radius: 4px;cursor: pointer;text-align: center;text-decoration: none;white-space: nowrap;transition: all 0.3s ease;&:hover {background-color: #0069d9;box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);}&:active {background-color: #0056b3;transform: translateY(1px);}} button {margin-top: 10px; display: inline-block;padding: 10px 20px;font-size: 16px;font-weight: bold;color: #ffffff;background-color: #007bff;border: none;border-radius: 4px;cursor: pointer;text-align: center;text-decoration: none;white-space: nowrap;transition: all 0.3s ease;&:hover {background-color: #0069d9;box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);}&:active {background-color: #0056b3;transform: translateY(1px);}}";
String style_css_body = "body {display: flex;justify-content: center;align-items: center;min-height: 100vh;margin: 0;padding: 0;box-sizing: border-box;background-color: #f0f0f0;}";
