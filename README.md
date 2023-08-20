# The-system-of-accounting-for-the-passage-of-testing-by-students

## About
The system is an implementation of the structure of the school educational system in C++ using an object-oriented approach. It allows you to enter, edit and analyze saved data via the console menu.

***

## Work of the system

* _Begin_
When the program starts, greeting, the rules for working with the system of accounting for the passage of testing of students and a menu for working directly with the system with numbered options for actions appear. The user should carefully read the rules of operation and the menu, and then select the desired action number. To get started, user needs to enter "1", i.e. choosing the option "Add a new class and evaluate its students on tests".
Selecting the necessary items in the system operation menu, which appears again after completing the previously selected action, prompts for entering values appear in front of the user.

* _1. Add a new class and its students' test scores_
When selecting the option "1. Add a new class and its students' test scores", the user consistently enters the name of the city, the name of the school, the name of the class teacher, the class number, the letter of the class, the number of subjects for which the tests were written, the maximum number of points for these tests, the number of students, the names of students and their test scores. The convenience of the system is manifested in the fact that first it outputs a hint – what needs to be entered, and after the user enters and presses the "Enter" key, it outputs the next hint.

* _2. Add a new student and his test scores_
When selecting option "2. Add a new student and his test scores" the user consistently enters the name of the city, the name of the school, the class number and the letter of the class to which he wants to add a new student. Then he enters his name, as well as grades on all the tests that were written by the class.

* _3. Add information on the test passed by the class_
When selecting the option "3. Add information on the test passed by the class", the user consistently enters the name of the city, the name of the school, the class number and the letter of the class that passed the new test. Then he enters the subject on which the test was taken, and then sequentially the scores of the students of this class on it.

* _4. Change the name of the teacher_
When selecting the option "4. Change the name of the teacher", the user consistently enters the name of the city, the name of the school, the class number and the letter of the class whose homeroom teacher he wants to change. Then he enters the name of the new teacher.

* _5. Change student data_
When selecting the option "5. Change student data" the user consistently enters the name of the city, the name of the school, the class number, the letter of the class and the name of the student whose information he wants to change.
Then the user chooses what he wants to change: the name or the test score. If the name, then he enters a new name, and if the score on the test, then selects the desired subject and enters a new number of points.

* _6. Delete a student_
When selecting the option "6. Delete a student", the user consistently enters the name of the city, the name of the school, the class number, the letter of the class and the name of the student he wants to delete.

* _7. Delete class_
When selecting the option "7. Delete class", the user consistently enters the name of the city, the name of the school, the class number and the letter of the class that he wants to delete.

* _8. Display all information_
When selecting the option "8. Display all information" all the information available in the system appears in front of the user.

* _9. Get information about a student_
When selecting the option "9. Get information about a student" the user consistently enters the name of the city, the name of the school, the class number, the letter of the class and the name of the student whose data he wants to view.

* _10. Get information about the class_
When selecting the option "10. Get information about the class" the user consistently enters the name of the city, the name of the school, the class number and the letter of the class about which he wants to view.

* _11. Get information about the school_
When selecting the option "11. Get information about the school", the user consistently enters the name of the city and the school that he wants to view data about.

* _12. Get information about the city_
When selecting the option "12. Get information about the city", all the stistic information available in the system appears in front of the user.

* _13. Exit_
When selecting the option "13. Exit" the inscription "F I N I S H" appears in front of the user, and the system operation is terminated.