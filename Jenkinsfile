pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                sh 'scripts/prepare_build.sh uts testing=ON'
                sh 'cd ../embedded_build/uts && make -j4'
            }
        }
        stage('Deploy') {
            steps {
                sh 'scripts/prepare_build.sh deploy testing=OFF'
                sh 'cd ../embedded_build/deploy && make -j4'
            }
        }
    }
}
