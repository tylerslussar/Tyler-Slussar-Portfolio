import java.util.Scanner;

public class QuestionAsker {
	String[] _responses;
	Question[] _questions;
	int _correctAnswers;
	
	public QuestionAsker(Question[] questions, String[] responses) {
		_questions = questions;
		_responses = responses;
		_correctAnswers = 0;
	}
	
	public static void main(String[] args) {
		String[] as = {"a", "b", "c", "d"};
		String[] temp1 = {"1", "2", "3", "4"};
		String[] temp2 = {"1.414", "1.000", "3.141", "2.718"};
		Question[] qs = {new Question("What is 1 + 1?", temp1, 1),
				new Question("Which is closest to the square root of 2?", temp2, 0)};
		QuestionAsker test = new QuestionAsker(qs, as);
		test.quiz();
		Functions.add(1, 2);
	}
	
	public void quiz() {
		// found how to read user input from https://www.geeksforgeeks.org/ways-to-read-input-from-console-in-java/
		// get a new reader
		Scanner in = new Scanner(System.in);
		// ask each question
		for (Question question : _questions) {
			// ask the question
			System.out.println(question.question());
			// print each response
			for (int i = 0; i < question.answers().length; ++i) {
				System.out.println(_responses[i] + ") " + question.answers()[i]);
			}
			boolean inResponses;
			// get the user's answer
			String given = getInput("Enter the letter that corresponds to your answer: ", in);
			do {
				String letterAnswer = _responses[question.correctAnswer()];
				// check to see if it's in the valid responses
				inResponses = false;
				for (String letter : _responses) {
					// == doesn't work, found .equals() from https://www.w3schools.com/java/ref_string_equals.asp
					inResponses = inResponses || given.equals(letter);
				}
				// tell them if their answer was correct and record it
				if (given.equals(letterAnswer)) {
					System.out.println("Correct!");
					_correctAnswers++;
				}
				// contains method found from https://stackabuse.com/java-check-if-array-contains-value-or-element/
				else if (inResponses) {
					System.out.println("Incorrect. The correct answer was " + letterAnswer + ".");
				}
				else {
					given = getInput(given + " is not a valid response. Please enter the letter that corresponds to your answer: ", in);
				}
			} while (!inResponses);
			// give the user a chance to look at their response
			// getInput("Press Enter to continue", in);
			System.out.println();
		}
		// close the input stream
		in.close();
		// report the score
		reportScore();
	}
	
	public static String getInput(String prompt, Scanner in) {
		// output the prompt and return the response
		System.out.print(prompt);
		return in.nextLine();
	}
	
	public void reportScore() {
		System.out.println();
		String answers = _correctAnswers == 1 ? "answer" : "answers";
		System.out.println("You got " + _correctAnswers + " " + answers + " correct out of " + _questions.length + ".");
		System.out.println("That's about " + _correctAnswers * 100 / _questions.length + "%!");
	}
}
