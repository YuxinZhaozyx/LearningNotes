# hugo themes - academic install note

## Install with Git

Prerequisites:

+ Git
+ Hugo Extend v0.55.6+

Install:

1. Fork the Academic Kickstart repository to create a new website

   - If you already created your site with **Netlify**, then skip this step

2. Clone your fork to your computer with Git, replacing `sourcethemes` in the command below with your GitHub username:

   ```
   git clone https://github.com/sourcethemes/academic-kickstart.git My_Website
   ```

3. Initialize the theme:

   ```
   cd My_Website
   git submodule update --init --recursive
   ```