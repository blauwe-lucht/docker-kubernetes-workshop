# Job and CronJob

A **Job** runs a Pod to completion and tracks its success. Use Jobs for one-off tasks: database migrations, data imports, report generation, or any work that has a clear end.

A **CronJob** creates Jobs on a schedule, the same way a cron entry runs a script.

## Job

Apply the Job:

```bash
kubectl apply -f job.yml
```

Watch it run:

```bash
kubectl get jobs -w
```

Once the `COMPLETIONS` column shows `1/1`, check the Pod status:

```bash
kubectl get pods
```

The Pod status will be `Completed` rather than `Running` — it did its work and exited. Read its output:

```bash
kubectl logs job/batch-job --timestamps
```

## CronJob

Apply the CronJob:

```bash
kubectl apply -f cronjob.yml
```

Check the schedule:

```bash
kubectl get cronjobs
```

The `SCHEDULE` column shows when it runs and `LAST SCHEDULE` shows when it last fired. The CronJob runs every minute, so wait up to 60 seconds and then watch Jobs appear:

```bash
kubectl get jobs -w
```

Each entry is a Job the CronJob created automatically. Read the output of the most recent one:

```bash
kubectl logs -l job-name --tail=20 --timestamps
```

## Clean up

```bash
kubectl delete -f job.yml
kubectl delete -f cronjob.yml
```
