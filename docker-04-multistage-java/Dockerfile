# Build stage
FROM maven:3.9-eclipse-temurin-21 AS builder

WORKDIR /app
COPY pom.xml .
COPY src ./src
RUN mvn package -q

# Final stage
FROM eclipse-temurin:21-jre-alpine

WORKDIR /app
COPY --from=builder /app/target/app.jar .

EXPOSE 8080
CMD ["java", "-jar", "app.jar"]
