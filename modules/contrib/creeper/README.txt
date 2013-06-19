======= SETUP INSTRUCTIONS =========

- Check out the latest aws asdk for php code from http://pear.amazonwebservices.com/get/sdk-1.2.3.zip and unzip it into the creeper directory.

  At this step you should have a sdk-1-x-y directory inside the creeper directory and inside this directory another sdk-1-x-y, rename this subdirectory "sdk" and delete the archive file file.

move the "sdk" subdirectory at the root of the creeper directory, and erase  his old parent directory sdk-x-y

- Move the file config.inc.php into the "sdk" directory.

- Then install it via the admin console of drupal and go in the Cloudfusion configuration menu in the admin section to fill your AWS account settings.

- You can now use the AWS SDK for PHP API in every module you will create that add a dependency to the creeper module ;-)

- If you're looking for API docs go to http://http://aws.amazon.com/sdkforphp/ 

