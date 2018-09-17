# Virtual Viva Examiner
A quiz maker for visually impaired students which selects questions randomly from the input file and reads them aloud.

This application needs a "questions.txt" file which contains multiple choice questions and their corresponding correct answers. The program reads this "questions.txt" file and randomly selects the questions from the file to create a quiz of "n" questions where "n" is input taken from the user. (Refer the sample "questions.txt" file for input file format.)

It has a "Read aloud" feature which means students can hear entire quiz read out loud. This can be especially useful for visually impaired students or for younger students who face reading difficulties.

This application is written in C++. For "Read aloud" feature, it uses SAPI (Speech Application Programming Interface), an API developed by Microsoft for speech recognition and speech synthesis within Windows applications.
