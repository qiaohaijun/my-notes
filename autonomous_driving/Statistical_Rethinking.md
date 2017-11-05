Statistical Rethinking
==

**A Bayesian Course with Examples in R and Stan**

### Materials

> Book: CRC Press, Amazon.com
> Book sample: Chapters 1 and 12 (2MB PDF)
> Winter 2015 Slides: Speakerdeck
> Winter 2015 Lectures: Youtube
> Code examples from the book: code.txt
> Solutions manual available to instructors (request an instructor inspection copy)
> Errata: [view on github]

#### What People Are Saying

> "This is a rare and valuable book that combines readable explanations, computer code, and active learning."
—Andrew Gelman, Columbia University

> "...an impressive book that I do not hesitate recommending for prospective data analysts and applied statisticians!"
—Christian Robert, Université Paris-Dauphine (review)

> "A pedagogical masterpiece..."
—Rasmus Bååth, Lund University

> "The content of this book has been developed over a decade+ of McElreath's teaching and mentoring of graduate students, post docs, and other colleagues, and it really shows."
—Brian Wood, Yale

> "...omg suddenly everything makes sense..."
—Ecstatic anonymous reader

#### Overview

Statistical Rethinking is an introduction to applied Bayesian data analysis, aimed at PhD students and researchers in the natural and social sciences. This audience has had some calculus and linear algebra, and one or two joyless undergraduate courses in statistics. I've been teaching applied statistics to this audience for about a decade now, and this book has evolved from that experience.

The book teaches generalized linear multilevel modeling (GLMMs) from a Bayesian perspective, relying on a simple logical interpretation of Bayesian probability and maximum entropy. The book covers the basics of regression through multilevel models, as well as touching on measurement error, missing data, and Gaussian process models for spatial and network autocorrelation.

This is not a traditional mathematical statistics book. Instead the approach is computational, using complete R code examples, aimed at developing skilled and skeptical scientists. Theory is explained through simulation exercises, using R code. And modeling examples are fully worked, with R code displayed within the main text. Mathematical depth is given in optional "overthinking" boxes throughout.

#### R package

The book is accompanied by an R package, rethinking. The core of this package is two functions, map and map2stan, that allow many different statistical models to be built up from standard model formulas. This has the virtue of forcing the user to lay out all of the assumptions. The function map performs maximum a posteriori fitting. The function map2stan builds a Stan model that can be used to fit the model using MCMC sampling. Some of the more advanced models in the last chapter are written directly in Stan code, in order to provide a bridge to a more general tool. The package is available here and from on github. There is also a technical manual with additional documentation.

#### Contents

- Preface
- Chapter 1: The Golem of Prague
- Chapter 2: Small Worlds and Large Worlds
- Chapter 3: Sampling the Imaginary
- Chapter 4: Linear Models
- Chapter 5: Multivariate Linear Models
- Chapter 6: Overfitting and Model Comparison
- Chapter 7: Interactions
- Chapter 8: Markov chain Monte Carlo Estimation
- Chapter 9: Big Entropy and the Generalized Linear Model
- Chapter 10: Counting and Classification
- Chapter 11: Monsters and Mixtures
- Chapter 12: Multilevel Models
- Chapter 13: Adventures in Covariance
- Chapter 14: Missing Data and Other Opportunities
- Chapter 15: Horoscopes

 
