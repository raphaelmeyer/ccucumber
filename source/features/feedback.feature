Feature: Scenario validation
  In order to delevop behavior driven
  As a C++ developer
  I want to get feedback about success or failure in steps and scenarios

  @wip
  Scenario: An undefined step
    Given a C++ wire server
    And the following feature:
      """
      Feature: feature
        Scenario: scenario
          Given an undefined step
      """
    When I run cucumber
    Then the output should contain:
      """
      1 scenario (1 undefined)
      1 step (1 undefined)
      """

