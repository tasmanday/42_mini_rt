/*
--> OG add_object
int	add_object(t_Scene *scene, struct Object *new_object)
{
	struct Object	*current;

	printf(G "   Entering" RST " add_object()\n\n");
	if (!scene)
	{
		printf("      Error: Scene is NULL.\n");
		return (0);
	}
	if (!new_object)
	{
		printf("      Error: New object is NULL.\n");
		return (0);
	}
	new_object->next = NULL;
	if (!scene->objects)
	{
		scene->objects = new_object;
		printf("      First object added to the scene!\n");
	}
	else
	{
		current = scene->objects;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_object;
	}
	scene->object_count++;
	printf(G "      Object added! New count: %d\n" RST, scene->object_count);
	print_objects_in_scene(scene->objects);
	printf(RED "\n   Exiting" RST " add_object()\n\n");
	return (SUCCESS);
}
*/