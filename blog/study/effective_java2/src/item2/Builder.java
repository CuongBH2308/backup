package item2;

/*
 * Other options when handle various constructor parameters:
 * 1. Telescope pattern: too many constructors, and very easy to be confused
 * 2. Java Beans pattern: object is in a inconsistent state when first created, and you have no idea when that is ready.
 */
class NutritionFacts {
	private final int servingSize;
	private final int servings;
	private final int calories;
	private final int fat;
	private final int carbohydrate;
	private final int sodium;

	// needs to be a static class
	// The builder collect the values first, and then pass all the pre-prepared the values
	// to the NutritionFacts at once in build(), to make sure the object is created in a 
	// clean yet consistent state
	public static class Builder {
		// Required parameters
		private final int servingSize;
		private final int servings;

		// Optional paramters, not final here as we need to change them
		private int calories = 0;
		private int fat = 0;
		private int carbohydrate = 0;
		private int sodium = 0;

		public Builder(int servingSize, int servings) {
			this.servingSize = servingSize;
			this.servings = servings;
		}
		
		public Builder calories(int value) {
			this.calories = value;
			return this; // return this, so the call could be chained
		}

		public Builder fat(int value) {
			this.fat = value;
			return this;
		}

		public Builder carbohydrate(int value) {
			this.carbohydrate = value;
			return this;
		}

		public Builder sodium(int value) {
			this.sodium = value;
			return this;
		}
		
		
		public NutritionFacts build() {
			return new NutritionFacts(this);
		}

	}

	// The constructor needs to be private, so it only get called in Builder.build()
	private NutritionFacts(Builder builder) {
		this.servingSize = builder.servingSize;
		this.servings = builder.servings;
        this.calories     = builder.calories;
        this.fat          = builder.fat;
        this.sodium       = builder.sodium;
        this.carbohydrate = builder.carbohydrate;
	}

	public static void main(String[] args) {
		// this resemble the optional key-value parameters in python
		NutritionFacts baiyanh = new NutritionFacts.Builder(240, 8).calories(400).sodium(60).build();

	}

}
