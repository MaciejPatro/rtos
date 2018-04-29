pipeline {
    agent any
    stages {
        stage('Build&Run UTs') {
            steps {
                sh 'scripts/prepare_build.sh uts testing=ON'
                sh 'cd ../embedded_build/uts && make -j4 && ctest -j4'
            }
        }
        stage('Build&Run Sanitizers') {
            steps {
                parallel(
                    Address: {
                        sh 'scripts/prepare_build.sh asan testing=ON asan=ON'
                        sh 'cd ../embedded_build/asan && make -j2 && ctest -j2'
                    },
                    Memory: {
                        sh 'scripts/prepare_build.sh msan testing=ON msan=ON'
                        sh 'cd ../embedded_build/msan && make -j2'
                        sh 'echo "Solve problem with std library and Catch..."'
                    },
                    Threads: {
                        sh 'scripts/prepare_build.sh tsan testing=ON tsan=ON'
                        sh 'cd ../embedded_build/tsan && make -j2 && ctest -j2'
                    }
                )
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
            sh 'cp ../embedded_build/uts/*.xml .'
            junit '*.xml'
            sh 'rm -rf *.xml'
        }
    }
}
