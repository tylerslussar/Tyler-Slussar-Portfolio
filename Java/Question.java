import java.util.Scanner;

public record Question(String question, String[] answers, int correctAnswer) {
	public String ask(Scanner in) {
		// ask the question
		System.out.println(question);
		// give possible answers
		for (String answer : answers) {
			System.out.println(answer);
		}
		// ask for a response
		System.out.print("Enter your response and press Enter: ");
		// give it to the caller
		return in.nextLine();
	}
}
