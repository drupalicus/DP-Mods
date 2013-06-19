// $Id$

Amazon SES Module for Drupal

REQUIREMENTS
------------
* An Amazon AWS account
* Creeper Module -- http://drupal.org/project/creeper

INSTALLATION INSTRUCTIONS
-------------------------
1.  Download and extract module to your Drupal sites/all/modules/ directory.
2.  Login as site administrator.
3.  Enable the Amazon SES module on the Administer -> Site
    building -> Modules page.
4.  Fill in required settings on the Administer -> Site configuration -> Amazon SES page.

NOTES
-----

Drupal will often use the email address entered into Administrator -> Site
configuration -> E-mail address as the from address.  This address must match your Amazon SES configuration on the Amazon AWS panel.