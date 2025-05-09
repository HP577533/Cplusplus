import numpy as np
from scipy import stats


# Rows      = [In-Person, Online]
# Columns   = [Pass, Fail]
observed = np.array([
    [145, 55],   # In-Person
    [120, 80]    # Online
])


# a. Row and column totals
row_totals = observed.sum(axis=1)     # Sum across rows
col_totals = observed.sum(axis=0)     # Sum down columns
grand_total = observed.sum()

print("Row Totals:", row_totals)
print("Column Totals:", col_totals)
print("Grand Total:", grand_total)

print("")
# Insert data into chi2 contingency function
chi_squared, p_value, degrees_of_freedom, exp_matrix = stats.chi2_contingency(observed=observed) 
# b. Degrees of freedom 
print("Degrees of Freedom:", degrees_of_freedom)

print("")
# c. Expected frequencies
print("Expected Frequencies:")
print(exp_matrix)

print("")
# d. Chi-square test statistic
print("Chi-square Test Statistic:", chi_squared)

print("")
# e. P-value
print("P-value:", p_value)

from scipy.stats import chi2

p_value = 1 - chi2.cdf(6.988, df=1)
print(p_value) 