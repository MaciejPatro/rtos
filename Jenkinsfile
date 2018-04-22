pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                sh 'scripts/prepare_build.sh uts testing=ON'
                sh 'cd ../embedded_build/uts && make -j4'
            }
        }
        stage('Run UTs') {
            steps {
                sh '../embedded_build/uts/stm32/ut/stm32_tests -r junit > ut_results.xml'
            }
        }
        stage('Deploy') {
            steps {
                sh 'scripts/prepare_build.sh deploy testing=OFF'
                sh 'cd ../embedded_build/deploy && make -j4'
            }
        }
    }
    post {
        always {
	        junit 'ut_results*.xml'
	    }
    }
