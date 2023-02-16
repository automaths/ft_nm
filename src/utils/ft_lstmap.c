t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy;
	t_list	*new;

	new = NULL;
	if (!f || !lst || !del)
		return (NULL);
	while (lst)
	{
		cpy = ft_lstnew(f(lst->content));
		if (!cpy)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, cpy);
		lst = lst->next;
	}
	return (new);
}
