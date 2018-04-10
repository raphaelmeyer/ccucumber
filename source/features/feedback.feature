Feature: Scenario validation
  In order to delevop behavior driven
  As a C++ developer
  I want to get feedback about success or failure in steps and scenarios

  @wip
  Scenario: A passing step
  Given a go wire server
  And the following feature:
    """
    Feature: feature
      Scenario: scenario
        Given a step which passes
    """
  When I run cucumber
  Then the output should contain:
    """
    1 scenario (1 passed)
    1 step (1 passed)
    """

